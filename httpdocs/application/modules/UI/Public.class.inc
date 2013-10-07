<?php

Config::addModuleToPath( 'application', 'Survey' );
Config::addModuleToPath( 'framework', 'Tal' );

class UI_Public {
	
	public function loadLogin( $args ) {
		$data = array();
		$data['jsInit'] = 'window.addEvent("domready",function(){ new LoginManager(); });';
		return new Tal_Tal( 'login/framework.tpl', $data );
	}
	
	public function loadSurvey( $args ) {
		if( !isset( $args['fkSurvey'] ) ) throw new Exception( "no survey specified" );
		$fkSurvey 		= (int)$args['fkSurvey'];
		$currentPhase = '';
		$title 				= 'Survey';
		try {
			$survey 			= Survey_PublicSurveyAdapter::getSurvey( $fkSurvey );
			$title 				= $survey['title'];
			$currentPhase = $survey['currentPhase'];
		} catch( Exception $e ) {
			$currentPhase = 'Not Found';
		}
		$data = array();
		
		$data['loadSurvey'] = "window.addEvent('domready',function(){ new SurveyDriver( '{$fkSurvey}', '{$currentPhase}' ); });";
		$data['title'] 		= $title;
		if( $currentPhase == 2 && isset( $_COOKIE[$fkSurvey] ) && $_COOKIE[$fkSurvey] == 'submitted' ) {
			$currentPhase = 2.5;
		}
		switch( $currentPhase ) {
			case 0 		: $data['macro'] 		= 'new'; 				break;
			case 1 		: $data['macro'] 		= 'phase1';	 		
									$data['description'] = $survey['phase1Description'];
									break;
			case 2 		: $data['macro'] 		= 'phase2';
									$data['description'] = $survey['phase2Description'];
									$data['entries'] 	= Survey_PublicSurveyAdapter::getEntries( $fkSurvey ); 
									break;
			case 2.5	: $data['macro'] 		= 'phase25';		break;
			case 3 		: $data['macro'] 		= 'complete'; 	break;
			default 	: $data['macro'] 		= 'notfound'; 	break;
		}
		return new Tal_Tal( 'survey/framework.tpl', $data );
	}

}

?>