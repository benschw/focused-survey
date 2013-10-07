<?php
Config::addModuleToPath( 'framework', 'JSON' );
Config::addModuleToPath( 'framework', 'Tal' );
Config::addModuleToPath( 'framework', 'CSV' );

class Survey_AdminSurvey {

	public function getHelp( $args ) {
		$type = ( isset( $args['type'] ) ? $args['type'] : null );
		return new Tal_Tal( 'home/help.tpl', array( 'type' => $type ) );
	}

	public function loadList( $args ) {
		$loginID 	= Session::singleton()->loginID;
		$type 		= ( isset( $args['id'] ) ? $args['id'] : 'empty' ); // new, active, complete

		$data = array();
		$data['isNew'] = ( $type == 'new' );
		if( $type == 'empty' ) {
			return new Tal_Tal( 'home/survey.list.tpl', $data );
		} else {
			switch( $type ) {
				case 'active'		: $data['heading'] = "Active Surveys";		break;
				case 'complete'	: $data['heading'] = "Complete Surveys";	break;
			}
			$data['surveys'] = Survey_SurveyListAdapter::getSurveys( $type, $loginID );
			return new Tal_Tal( 'home/survey.list.panel.tpl', $data );
		}
	}
	public function loadInstructions( $args ) {
		$type = ( isset( $args['id'] ) ? $args['id'] : 'empty' ); // empty, active, complete
		return new Tal_Tal( 'home/survey.tool.instructions.tpl', array( 'type' => $type ) );
	}
	public function add( $args ) {
		try {
			$loginID = Session::singleton()->loginID;

			Survey_SurveyListAdapter::add( $loginID );
			return new JSON_JSON( array( "result" => true ) );
		} catch( Exception $e ) {
			return new JSON_JSON( array( "result" => false, 'message' => $e->getMessage() ) );
		}
	}

	public function rename( $args ) {
		try {
			if( !isset( $args['id'] ) ) 			throw new Exception( "Required id is missing" );
			if( !isset( $args['newName'] ) ) 	throw new Exception( "Required newName is missing" );
			$loginID  = Session::singleton()->loginID;
			$fkSurvey = $args['id'];
			$newName  = $args['newName'];

			Survey_SurveyListAdapter::rename( $loginID, $fkSurvey, $newName );
			return new JSON_JSON( array( "result" => true ) );
		} catch( Exception $e ) {
			return new JSON_JSON( array( "result" => false, 'message' => "Sorry but you aren't allowed to rename this" ) );
		}
	}

	public function load( $args ) {
		try {
			if( !isset( $args['id'] ) ) throw new Exception( "no survey specified" );
			$loginID  = Session::singleton()->loginID;
			$fkSurvey = ( isset( $args['id'] ) ? $args['id'] : 1 );
			$survey   = Survey_AdminSurveyAdapter::getSurvey( $loginID, $fkSurvey );
			
			return new Tal_Tal( 'home/survey.tools.tpl', $survey );
		} catch( Exception $e ) {
			die( "there was a problem processing your request\n<br />" . $e->getMessage() );
		}
	}
	public function downloadReport( $args ) {
		try {
			if( !isset( $args['fkSurvey'] ) ) throw new Exception( "no survey specified" );
			$loginID  = Session::singleton()->loginID;
			$fkSurvey = ( isset( $args['fkSurvey'] ) ? $args['fkSurvey'] : 1 );
			$survey   = Survey_AdminSurveyAdapter::getSurvey( $loginID, $fkSurvey );
			return new CSV_CSV( $survey['title'] . ".csv", Survey_AdminSurveyLib::getEntriesForDownload( $fkSurvey ) );
		} catch( Exception $e ) {
			die( "there was a problem processing your request\n<br />" . $e->getMessage() );
		}
	}
	public function save( $uiData ) {
		try {
			if( !isset( $uiData['id'] ) ) throw new Exception( "Required id is missing" );
			$loginID 	= Session::singleton()->loginID;
			$fkSurvey = $uiData['id'];

			$errors = Survey_AdminSurveyAdapter::save( $loginID, $fkSurvey, $uiData );

			if( count( $errors ) > 0 ) {
				return new JSON_JSON( array( "result" => true, 'errors' => true, 'message' => implode( "\n", $errors ) ) );
			} else {
				return new JSON_JSON( array( "result" => true, 'errors' => false ) );	
			}
		} catch( Exception $e ) {
			return new JSON_JSON( array( "result" => false, 'message' => $e->getMessage() ) );
		}
	}
}
?>