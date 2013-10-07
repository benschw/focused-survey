<?php

Config::addModuleToPath( 'application', 'Survey' );
Config::addModuleToPath( 'framework', 'Tal' );
Config::addModuleToPath( 'framework', 'JSON' );

class Survey_PublicSurvey {
	
	public function addEntry( $args ) {
		try {
			if( !isset( $args['id'] ) ) 																	throw new Exception( "no survey specified" );
			if( !isset( $args['newEntry'] ) || $args['newEntry'] == '' ) 	throw new Exception( "New Entry Cannot be Blank" );
			$fkSurvey = (int)$args['id'];
			$newEntry = $args['newEntry'];
			Survey_PublicSurveyAdapter::addEntry( $fkSurvey, $newEntry );
			return new JSON_JSON( array( "result" => true ) );
		} catch( Exception $e ) {
			return new JSON_JSON( array( "result" => false, 'message' => $e->getMessage() ) );
		}
	}

	public function getNewEntries( $args ) {
		try {
			if( !isset( $args['id'] ) )		throw new Exception( "No survey specified" );
			$fkSurvey  = (int)$args['id'];
			$time1     = ( isset( $args['time'] ) ? $args['time'] : 0 );
			$time2     = time();
			sleep(1);
			$entries   = Survey_PublicSurveyAdapter::getEntries( $fkSurvey, $time1, $time2 );
			$entryHTML = array();
			foreach( $entries AS $entry ) {
				$tal         = new Tal_Tal( 'survey/entry.tpl', $entry );
				$entryHTML[] = $tal->getRendered();
			}
			return new JSON_JSON( array( "result" => true, 'time' => $time2, 'entries' => $entryHTML ) );
		} catch( Exception $e ) {
			return new JSON_JSON( array( "result" => false, 'message' => $e->getMessage() ) );
		}
	}

	public function submitRatings( $args ) {
		try {
			if( !isset( $args['id'] ) )         throw new Exception( "No survey specified" );
			if( !isset( $args['values'] ) )     throw new Exception( "No ratings specified" );
			if( !is_array( $args['values'] ) )  throw new Exception( "Ratings data must be an array" );
			$fkSurvey = (int)$args['id'];
			$ratings  = $args['values'];
			Survey_PublicSurveyAdapter::recordRatings( $fkSurvey, $ratings );

			return new JSON_JSON( array( "result" => true ) );
		} catch( Exception $e ) {
			return new JSON_JSON( array( "result" => false, 'message' => $e->getMessage() ) );
		}
	}
	
	public function runCron( $args ) {
		try {
			$cron = Survey_Cron::find();
			Survey_Cron::send( $cron );
			return new JSON_JSON( array( "result" => true ) );
		} catch( Exception $e ) {
			return new JSON_JSON( array( "result" => false, 'message' => $e->getMessage() ) );
		}
	}

}

?>