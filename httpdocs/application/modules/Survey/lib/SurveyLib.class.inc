<?php
Config::addModuleToPath( 'application', 'Account' );

class Survey_SurveyLib {

	//==========================================================================
	// Load
	//==========================================================================

	public static function getSurvey( $fkSurvey ) {
		$fkSurvey = (int)$fkSurvey;
		$survey 	= Mysql::singleton()->selectRecord( "SELECT * FROM Survey WHERE id = {$fkSurvey}" );	
		if( count( $survey ) == 0 ) throw new Exception( "Survey Not Found" );
		return $survey;
	}
	
	public static function getEntries( $fkSurvey, $t1 = 0, $t2 = 0 ) {
		$fkSurvey = (int)$fkSurvey;
		$t1 			= (int)$t1;
		$t2 			= (int)$t2;
		$filter 	= ( $t2 != 0 ? "AND created <= {$t2}" : "" );
		return Mysql::singleton()->select( "SELECT id, content, created
		                                      FROM Entry 
		                                     WHERE fkSurvey = {$fkSurvey} 
		                                       AND created > {$t1} 
		                                           {$filter}
		                                       AND isDeleted = false 
		                                  ORDER BY created" );
	}

	public static function getCurrentPhase( $data ) {
		$state = '';
		if( $data['scheduleType'] == 'schedule' ) {
			$now = time();
			if( 	 $data['phase1Start'] == 0 
					|| $data['phase2Start'] == 0
					|| $data['end'] == 0 
					|| ( $data['phase1Start'] > $data['phase2Start'] ) 
					|| ( $data['phase2Start'] > $data['end'] ) ) {
				$state = 'new';
			} else if( $now < $data['phase1Start'] ) {
				$state = 'new';
			} else if( $now >= $data['phase1Start'] && $now <= $data['phase2Start'] ) {
				$state = 'phase1';
			} else if( $now >= $data['phase2Start'] && $now <= $data['end'] ) {
				$state = 'phase2';
			} else if( $now >= $data['end'] ) {
				$state = 'end';
			} else {
				$state = 'new';
			}
		} else if( $data['scheduleType'] == 'toggle' ) {
			$state = $data['toggleState'];
		} 
		switch( $state ) {
			case 'new' : return 0;
			case 'phase1' : return 1;
			case 'phase2' : return 2;
			case 'end' : 
			case 'complete' : return 3;
			default : throw new Exception( "unknown scheduling mechanism: {$state}" );
		}
	}
	
	//==========================================================================
	// Save
	//==========================================================================
	
	public static function addEntry( $fkSurvey, $entry ) {
		$fkSurvey = (int)$fkSurvey;
		$entry		= Mysql::escapeString( $entry );
		$time 		= time();
		Mysql::singleton()->insert( "INSERT INTO Entry 
																						 ( `fkSurvey`, `content`, `created` ) 
																 			VALUES ( {$fkSurvey}, '{$entry}', {$time} )" );
	}

}

?>