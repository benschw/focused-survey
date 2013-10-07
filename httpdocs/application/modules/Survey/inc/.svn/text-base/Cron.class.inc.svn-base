<?php

class Survey_Cron {
	
	private $from    = 'noreply@example.com';
	private $surveys = array();
	
	public function __construct() {
		$domain = Utilities::getServerName();
		if( substr( $domain, 0, 4 ) == 'www.' ) {
			$domain = substr( $domain, 4 );
		}
		$this->from = "noreply@{$domain}";
	}
	
	public function getSurveys() {
		return $this->surveys;
	}
	public function addSurvey( $phase, $id, $title, $subject, $body, $url, $emails ) {
		$tmp = array();
		$tmp['phase']    = $phase;
		$tmp['id']       = $id;
		$tmp['title']    = $title;
		$tmp['subject']  = $subject;
		$tmp['body']     = $body;
		$tmp['url']      = $url;
		$tmp['emails']   = $emails;
		$this->surveys[] = $tmp;
	}

	public static function send( Survey_Cron $cron ) {
		$db      = Mysql::singleton();
		$surveys = $cron->getSurveys();
		foreach( $surveys AS $survey ) {
			foreach( $survey['emails'] AS $email ) {
				$mailer = new Mailer();
				$mailer->setTo( $email );
				$mailer->setFrom( $cron->from );
				$mailer->setSubject( $survey['subject'] );
				$mailer->setBody( $survey['body'] . 
				                  "\r\n\r\nPlease follow the link below to participate in this survey.\r\n\r\n " . $survey['url'] );
				$mailer->send();
			}
			$fkSurvey = (int)$survey['id'];
			$newState = (int)$survey['phase'];
			$db->update( "UPDATE Survey SET emailState = {$newState} WHERE id = {$fkSurvey}" );
		}
	}

	public static function find() {
		$db = Mysql::Singleton();
		$time = time();
		$surveys = $db->select( "SELECT S.id, S.emailState, S.title, 
		                                S.phase1Start, S.phase2Start, S.end,
		                                S.phase1Subject, S.phase1Body,
		                                S.phase2Subject, S.phase2Body
		                           FROM Survey S 
		                          WHERE S.scheduleType = 'schedule' 
		                            AND S.end > {$time}                        -- survey hasn't expired
		                            AND S.phase1Start != 0                     -- survey has been configured
		                            AND S.phase2Start != 0
		                            AND S.phase2Start > S.phase1Start          -- survey has been configured correctly
		                            AND S.end > S.phase2Start
		                            AND (    (     S.emailState < 1            -- need to send phase1 email
		                                       AND S.phase1Start <= {$time} )
		                                  OR (     S.emailState < 2            -- need to send phase2 email
		                                       AND S.phase2Start <= {$time} )
		                                )" );
		$cron = new Survey_Cron();
		foreach( $surveys AS $survey ) {
			(int)$fkSurvey = $survey['id'];
			$users         = $db->selectIterator( "SELECT email 
			                                         FROM Participant 
			                                        WHERE fkSurvey = {$fkSurvey}" );

			if( $survey['phase1Start'] <= $time && $survey['emailState'] < 1 ) {
				$cron->addSurvey( 1, (int)$survey['id'], (string)$survey['title'], 
				                  (string)$survey['phase1Subject'], 
				                  (string)$survey['phase1Body'], 
				                  Config::$baseUrl . 'survey/' . $survey['id'], 
				                  $users );
			}
			if( $survey['phase2Start'] <= $time && $survey['emailState'] < 2 ) {
				$cron->addSurvey( 2, (int)$survey['id'], (string)$survey['title'], 
				                  (string)$survey['phase2Subject'], 
				                  (string)$survey['phase2Body'], 
				                  Config::$baseUrl . 'survey/' . $survey['id'], 
				                  $users );
			}
		}
		
		return $cron;
	}

}

?>