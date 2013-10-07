<?php
Config::addModuleToPath( 'application', 'Account' );

class Survey_PublicSurveyAdapter {

	public static function getSurvey( $fkSurvey ) {
		$data 								= Survey_SurveyLib::getSurvey( $fkSurvey );
		$data['currentPhase'] = Survey_SurveyLib::getCurrentPhase( $data );

		return $data;
	}

	public static function getEntries( $fkSurvey, $time1 = 0, $time2 = 0 ) {
		$fkSurvey = (int)$fkSurvey;
		$entries 	= Survey_SurveyLib::getEntries( $fkSurvey, $time1, $time2 );
		$clean 		= array();
		for( $i = 0; $i < count( $entries ); $i++ ) {
			$tmp = array();
			$tmp['id'] 					= $entries[$i]['id'];
			$tmp['content'] 		= $entries[$i]['content'];
			$tmp['class'] 			= ( $time1 != 0 ? 'new entry' : 'entry' );
			$clean[] = $tmp;
		}
		return $clean;
	}
	
	public static function addEntry( $fkSurvey, $entry ) {
		Survey_SurveyLib::addEntry( $fkSurvey, $entry );
	}
	
	public static function recordRatings( $fkSurvey, $values ) {
		$db = Mysql::singleton();
		foreach( $values AS $fkEntry => $value ) {
			if( $value > 100 )             throw new Exception( "This rating seems irrational" );
			if( $value < -1 )              throw new Exception( "This rating seems irrational" );
			if( !is_numeric( $value ) )    throw new Exception( "This rating seems irrational" );
			if( !is_numeric( $fkEntry ) )  throw new Exception( "This rating seems irrational" );
			$fkEntry = (int)$fkEntry;
			$value   = (int)$value;
			$time    = time();
			$db->update( "INSERT INTO EntryResponse 
			                          ( `fkEntry`, `rating`, `time` )
			                   VALUES ( $fkEntry, $value, $time )" );
		
		}
	}
	
}
?>