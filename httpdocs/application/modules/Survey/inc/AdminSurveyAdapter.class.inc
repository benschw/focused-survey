<?php

class Survey_AdminSurveyAdapter {

	public static function getSurvey( $loginID, $fkSurvey ) {
		$prefs = Survey_SurveyLib::getSurvey( $fkSurvey );
		
		$data = array();
		// Meta
		$data['id'] 		= $prefs['id']; // make this less incremental
		$data['uniqueID'] 		= $prefs['id']; // make this less incremental
		$data['title'] 				= $prefs['title'];
		$data['created'] 			= date( "n/j/y g:ia", $prefs['created'] );
		$data['url'] 					= Config::$baseUrl . 'survey/' . $data['uniqueID'];
		$data['currentPhase'] = Survey_SurveyLib::getCurrentPhase( $prefs );
		$data['tools']				= Survey_AdminSurveyLib::getAllowedTools( $loginID, $fkSurvey, $data['currentPhase'] );
		if( count( $data['tools'] ) == 0 ) throw new Exception( "This survey doesn't seem to belong to you" );
		$data['tabs'] 				= self::getTabs( $data['tools'] );
		
		$p1Default = "[topic entered by the admin goes here] \n\nPlease enter short (a phrase or a sentence) comments on this topic.  There is no reason to repeat comments that other respondents have already entered.  Each of your comments should be a single point to which other respondents might agree or disagree.  If you have two or more points, enter them as separate items.";
		$p2Default = "[NOTE: Survey topic should NOT reappear here, should it?  If not, that needs to be change on admin page] \n\nPlease indicate your level of agreement with each of the comments listed here by clicking on the appropriate buttons.  These are the comments that participants entered in Phase One of this survey, as edited and supplemented by the survey administrator.";
		
		// General
		$data['phase1Description'] 	= ( $prefs['phase1Description'] == '' ? $p1Default 	: $prefs['phase1Description'] );
		$data['phase2Description'] 	= ( $prefs['phase2Description'] == '' ? $p2Default 	: $prefs['phase2Description'] );
		$data['phase1Subject'] 			= ( $prefs['phase1Subject'] 		== '' ? Config::$settings['defaults']['phase1Subject'] 			: $prefs['phase1Subject'] );
		$data['phase2Subject'] 			= ( $prefs['phase2Subject'] 		== '' ? Config::$settings['defaults']['phase2Subject'] 			: $prefs['phase2Subject'] );
		$data['phase1Body'] 				= ( $prefs['phase1Body'] 				== '' ? Config::$settings['defaults']['phase1Body'] 				: $prefs['phase1Body'] );
		$data['phase2Body'] 				= ( $prefs['phase2Body'] 				== '' ? Config::$settings['defaults']['phase2Body'] 				: $prefs['phase2Body'] );
		// Schedule Type
		$data['scheduleType'] 				= $prefs['scheduleType'];
		$data['isScheduled'] 					= ( $prefs['scheduleType'] == 'schedule' );
		$data['isToggled'] 						= ( $prefs['scheduleType'] == 'toggle' );
		// Toggle Type
		$data['toggleState'] 					= $prefs['toggleState'];
		$data['toggle'] 							= array();
		$data['toggle']['isNew'] 			= ( $data['toggleState'] == 'new' );
		$data['toggle']['isPhase1'] 	= ( $data['toggleState'] == 'phase1' );
		$data['toggle']['isPhase2'] 	= ( $data['toggleState'] == 'phase2' );
		$data['toggle']['isComplete'] = ( $data['toggleState'] == 'complete' );
		// Schedule Times
		$data['phase1Start'] 		= ( $prefs['phase1Start'] == 0 ? '' : date( "m/d/Y", $prefs['phase1Start'] ) );
		$data['phase2Start'] 		= ( $prefs['phase2Start'] == 0 ? '' : date( "m/d/Y", $prefs['phase2Start'] ) );
		$data['end'] 						= ( $prefs['end'] == 0 ? '' : date( "m/d/Y", $prefs['end'] ) );
		// The Rest
		$data['administrators']	= Survey_AdminSurveyLib::getAdministrators( $fkSurvey ); 
		$data['participants']		= implode( ", ", Survey_AdminSurveyLib::getParticipants( $fkSurvey ) );
		$data['entries']				= Survey_AdminSurveyLib::getEntries( $fkSurvey );
		for( $i = 0; $i < count( $data['entries'] ); $i++ ) {
			$data['entries'][$i]['isDeleted'] = (bool)$data['entries'][$i]['isDeleted'];
			$id = $data['entries'][$i]['id'];
			$data['entries'][$i]['class'] = ( $data['entries'][$i]['isDeleted'] ? "{$id} deleted" : $id );
		}
		$data['timesRated'] = 0;
		$data['reports'] = array();

		$deleted = array();
		foreach( $data['entries'] AS $entry ) {
			$entry['noOpinion'] = 0;
			if( count( $entry['data'] ) == 0 ) {
				$entry['average'] = 'n/a';
				$entry['median'] = 'n/a';
			} else {
				$tmp = $entry['data'];
				$entry['data'] = array();
				foreach( $tmp AS $val ) {
					if( $val == -1 ) {
						$entry['noOpinion']++;
					} else {
						$entry['data'][] = $val;
					}
				}
				sort( $entry['data'] );
				$entry['average'] = sprintf( "%.2f", array_sum( $entry['data'] ) / count( $entry['data'] ) - 50 );
				$entry['median']	= sprintf( "%.2f", $entry['data'][ round( count( $entry['data'] ) / 2 ) - 1 ] - 50 );
			}
			$entry['class'] = ( $entry['moderated'] ? 'moderated' : '' );
			$entry['class'] = ( $entry['isDeleted'] ? 'deleted' : $entry['class'] );
			if( $entry['isDeleted'] ) {
				$deleted[] = $entry;
			} else {
				$data['timesRated'] = max( $data['timesRated'], count( $entry['data'] ) );
				$data['reports'][] = $entry;
			}
		}
		$data['reports'] = array_merge( $data['reports'], $deleted );
		return $data;
	}

	public static function save( $loginID, $fkSurvey, $uiData ) {
		$errors = array();
		$survey 			= Survey_SurveyLib::getSurvey( $fkSurvey );
		$currentPhase = Survey_SurveyLib::getCurrentPhase( $survey );
		$tools				= Survey_AdminSurveyLib::getAllowedTools( $loginID, $fkSurvey, $currentPhase );

		if( isset( $uiData['general'] ) 	&& in_array( 'general', $tools ) ) {
			$errors = array_merge( $errors, Survey_AdminSurveyLib::saveGeneral( $uiData['id'], $uiData['general'] ) );
		}
		if( isset( $uiData['schedule'] ) 	&& in_array( 'schedule', $tools ) ) {
			$errors = array_merge( $errors, Survey_AdminSurveyLib::saveSchedule( $uiData['id'], $uiData['schedule'] ) );
		}
		if( isset( $uiData['admins'] ) 		&& in_array( 'admins', $tools ) ) {
			$errors = array_merge( $errors, Survey_AdminSurveyLib::saveAdministrators( $uiData['id'], $uiData['admins'] ) );
		}
		if( isset( $uiData['users'] ) 		&& in_array( 'users', $tools ) ) {
			$errors = array_merge( $errors, Survey_AdminSurveyLib::saveParticipants( $uiData['id'], $uiData['users'] ) );
		}
		if( isset( $uiData['moderate'] ) 	&& in_array( 'moderate', $tools ) ) {
			$errors = array_merge( $errors, Survey_AdminSurveyLib::saveEntries( $uiData['id'], $uiData['moderate'] ) );
		}
		
		return $errors;
	}
	
	//==========================================================================
	private static function getTabs( $toolsArr ) {		
		$tools = array();
		foreach( $toolsArr AS $tool ) {
			$tmp = array();
			$tmp['id'] 					= $tool;
			$tmp['panelID'] 		= "{$tool}Panel";
			$tmp['panelClass'] 	= 'hidden toolPanel';
			$tmp['name'] 				= ucfirst( $tool );
			$tools[] = $tmp;
		}
		$tools[0]['class'] 			= 'selected';
		$tools[0]['panelClass'] = 'toolPanel';

		return $tools;
	}
	
}

?>