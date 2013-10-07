<?php

class Survey_SurveyListAdapter {
	
	public static function add( $loginID ) {
		$fkUser = (int)$loginID;
		$time 	= time();
		$names = Mysql::singleton()->selectColumn( "SELECT S.title FROM Survey S INNER JOIN UserSurveyMap M ON S.id = M.fkSurvey WHERE M.fkUser = {$fkUser}" );
		$title = NameLib::getNewName( $names, "New Survey" );
		$newID = Mysql::singleton()->insert( "INSERT INTO Survey ( title, created ) VALUES ( '{$title}', {$time} )" );
		Mysql::singleton()->insert( "INSERT INTO UserSurveyMap ( fkUser, fkSurvey ) VALUES ( {$fkUser}, {$newID} )" );
	}

	public static function rename( $loginID, $fkSurvey, $newName ) {
		$fkUser 	= (int)$loginID;
		$fkSurvey = (int)$fkSurvey;
		$newName	= Mysql::escapeString( $newName );
		$hasPermissions = (bool)Mysql::singleton()->count( "SELECT count(*) FROM Survey S INNER JOIN UserSurveyMap M ON S.id = M.fkSurvey WHERE M.fkUser = {$fkUser} AND S.id = {$fkSurvey} AND M.canModifyGeneral = TRUE" );
		if( !$hasPermissions ) throw new Exception( "You don't seem to be allowed to rename this survey" );

		Mysql::singleton()->update( "UPDATE Survey SET title = '{$newName}' WHERE id = {$fkSurvey}" );
	}


	public static function getSurveys( $type, $loginID ) {
		$fkUser = (int)$loginID;
		$time 	= time();
		$toggleFilter 	= "";
		$scheduleFilter = "";
	
		switch( $type ) { // Toggled
			case 'new' 			: 
			case 'active' 	: $toggleFilter = "S.toggleState IN ( 'new', 'phase1', 'phase2' )";	break;
			case 'complete'	: $toggleFilter = "S.toggleState IN ( 'complete' )"; 								break;
		}
		switch( $type ) { // Scheduled
			case 'new' 			: 
			case 'active' 	: $scheduleFilter = "( S.end > {$time} || S.end = 0 )";	break;
			case 'complete' : $scheduleFilter = "( S.end < {$time} && S.end != 0 )";	break;
		
		}
		$surveys = Mysql::singleton()->select( 
												 "SELECT S.id, S.title, S.created
														FROM Survey S 
											INNER JOIN UserSurveyMap M ON S.id = M.fkSurvey 
													 WHERE M.fkUser = {$fkUser} 
													 	 AND ( ( S.scheduleType = 'toggle' AND {$toggleFilter} )
																OR ( S.scheduleType = 'schedule' AND {$scheduleFilter} ) )
												ORDER BY S.created DESC" );
		return $surveys;
	}
	
}
?>