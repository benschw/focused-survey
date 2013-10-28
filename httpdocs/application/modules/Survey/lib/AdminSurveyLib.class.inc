<?php
Config::addModuleToPath( 'application', 'Account' );

class Survey_AdminSurveyLib {

	//==========================================================================
	// Load
	//==========================================================================
	
	public static function getAllowedTools( $loginID, $fkSurvey, $currentPhase ) {
		$fkUser = (int)$loginID;
		$fkSurvey = (int)$fkSurvey;
		$prefs = Mysql::singleton()->selectRecord( 
			"SELECT * 
			FROM UserSurveyMap 
			WHERE fkUser = {$fkUser} 
			AND fkSurvey = {$fkSurvey}" 
		);
		
		if( !(bool)$prefs ) throw new Exception( "This survey doesn't seem to belong to you" );

		$tools = array();
		if( (bool)$prefs['canModifyGeneral'] ) 														$tools[] = 'general';
		if( (bool)$prefs['canSchedule'] ) 																$tools[] = 'schedule';
		if( (bool)$prefs['canManageAdmins'] ) 														$tools[] = 'admins';
		if( (bool)$prefs['canModerate'] && $currentPhase < 2 ) 						$tools[] = 'moderate';
		if( (bool)$prefs['canManageParticipants'] && $currentPhase < 3 ) 	$tools[] = 'users';
		if( (bool)$prefs['canViewReports'] && $currentPhase == 3 )				$tools[] = 'reports';
		return $tools;
	}
	
	public static function getAdministrators( $fkSurvey ) {
		$fkSurvey = (int)$fkSurvey;		
		return Mysql::singleton()->select( "SELECT U.email, M.* 
																					FROM UserSurveyMap M 
																		INNER JOIN User U ON M.fkUser = U.id 
																				 WHERE M.fkSurvey = {$fkSurvey}" );
	}
	public static function getParticipants( $fkSurvey ) {
		$fkSurvey = (int)$fkSurvey;		
		return Mysql::singleton()->selectColumn( "SELECT email FROM Participant WHERE fkSurvey = {$fkSurvey}" );
	}

	public static function getEntries( $fkSurvey ) {
		$db = Mysql::singleton();
		$fkSurvey = (int)$fkSurvey;
		$entries = $db->select( "SELECT E.id, E.content, E.created, E.isDeleted, E.moderated
													 		 FROM Entry E
															WHERE E.fkSurvey = {$fkSurvey} 
											 		 ORDER BY E.created" );

		$entryData = $db->select( "SELECT ER.fkEntry, ER.rating
													 		 	 FROM Entry E
												 	 INNER JOIN EntryResponse ER ON ER.fkEntry = E.id
																WHERE E.fkSurvey = {$fkSurvey} 
											 			 ORDER BY E.created" );
		for( $i = 0; $i < count( $entries ); $i++ ) {
			$entries[$i]['data'] = array();
			foreach( $entryData AS $result ) {
				if( $entries[$i]['id'] == $result['fkEntry'] ) {
					$entries[$i]['data'][] = $result['rating'];
				}
			}
		}
		return $entries;
	}
	public static function getEntriesForDownload( $fkSurvey ) {
		$db       = Mysql::singleton();
		$fkSurvey = (int)$fkSurvey;

		return $db->selectIterator( "SELECT E.content, ER.rating
		                               FROM Entry E
		                         INNER JOIN EntryResponse ER ON ER.fkEntry = E.id
		                              WHERE E.fkSurvey = {$fkSurvey} 
		                           ORDER BY E.created" );
	}
	
	//==========================================================================
	// Save
	//==========================================================================
	
	public static function saveGeneral( $id, $args ) {
		$id = (int)$id;
		$title 							= Mysql::escapeString( $args['title'] );
		$phase1Description 	= Mysql::escapeString( $args['phase1Description'] );
		$phase1Subject 			= Mysql::escapeString( $args['phase1Subject'] );
		$phase1Body 				= Mysql::escapeString( $args['phase1Body'] );
		$phase2Description 	= Mysql::escapeString( $args['phase2Description'] );
		$phase2Subject 			= Mysql::escapeString( $args['phase2Subject'] );
		$phase2Body 				= Mysql::escapeString( $args['phase2Body'] );
		
		Mysql::singleton()->update( "UPDATE Survey 
																		SET title 						= '{$title}',
																				phase1Description = '{$phase1Description}',
																				phase1Subject 		= '{$phase1Subject}',
																				phase1Body 				= '{$phase1Body}',
																				phase2Description = '{$phase2Description}',
																				phase2Subject 		= '{$phase2Subject}',
																				phase2Body 				= '{$phase2Body}'
																	WHERE id = {$id}" );
		return array();																		
	}
	public static function saveSchedule( $id, $args ) {
		$errors         = array();
		$id             = (int)$id;
		$schedulingType = Mysql::escapeString( $args['schedulingType'] );
		$toggleMode     = Mysql::escapeString( $args['toggleMode'] );
		$phase1         = self::getTimeFromHuman( $args['phase1'] );
		$phase2         = self::getTimeFromHuman( $args['phase2'] );
		$end            = self::getTimeFromHuman( $args['end'] );
		if( $schedulingType == 'schedule' ) {
			if( $phase2 < $phase1 ) $errors[] = "Phase-2 Start shouldn't be before Phase-1 Start";
			if( $end < $phase2 )    $errors[] = "Survey End-Date shouldn't be before Phase-2 Start";
		}
		if( !in_array( $schedulingType, array( 'toggle', 'schedule' ) ) ) 
			throw new Exception( "Unknown schedulingType: {$schedulingType}" );
		if( !in_array( $toggleMode, array( 'new', 'phase1', 'phase2', 'complete' ) ) ) 
			throw new Exception( "Unknown toggleMode: {$toggleMode}" );

		Mysql::singleton()->update( "UPDATE Survey
		                                SET phase1Start   = '{$phase1}', 
		                                    phase2Start   = '{$phase2}', 
		                                    end           = '{$end}',
		                                    scheduleType  = '{$schedulingType}',
		                                    toggleState   = '{$toggleMode}'
		                              WHERE id = {$id}" );
		return $errors;
	}
	
	public static function saveParticipants( $id, $args ) {
		$db     = Mysql::singleton();
		$errors = array();
		$id     = (int)$id;
		$raw    = explode( ',', trim( $args ) );
		$clean  = array();
		foreach( $raw AS $user ) {
			if( trim( $user ) != '' ) {
				if( TypeUtil::isEmail( $user ) ) {
					$clean[]  = trim( $user );
				} else {
					$errors[] = "$user was not add to participants list. Not a valid email.";
				}
			}
		}
		$existing = $db->selectColumn( "SELECT email FROM Participant WHERE fkSurvey = {$id}" );
		$toAdd    = array_diff( $clean, $existing );
		$toDel    = array_diff( $existing, $clean );
		if( count( $toAdd ) > 0 ) {
			$arr = array();
			foreach( $toAdd AS $email ) {
				$email = Mysql::escapeString( $email );
				$arr[] = "( {$id}, '{$email}' )";
			}
			$str = implode( ", ", $arr );
			$db->insert( "INSERT INTO Participant ( fkSurvey, email ) VALUES {$str}" );
		}
		if( count( $toDel ) ) {
			$arr = array();
			foreach( $toDel AS $email ) {
				$email = Mysql::escapeString( $email );
				$arr[] = "'{$email}'";
			}
			$toDel = implode( ", ", $arr );
			$db->delete( "DELETE FROM Participant WHERE fkSurvey = {$id} AND email IN ( {$toDel} )" );
		}
		return $errors;
	}
	public static function saveEntries( $id, $args ) {
		$db       = Mysql::singleton();
		$fkSurvey = (int)$id;
		$time     = time();
		foreach( $args AS $entry ) {
			$id        = (int)( $entry['id'] == 'new' ? -1 : $entry['id'] );
			$isDeleted = (int)( $entry['isDeleted'] == 'true' );
			
			if( $id == -1 ) {
				if( !$isDeleted ) {
					$entry = Mysql::escapeString( $entry['entry'] );
					$db->insert( "INSERT INTO Entry 
					                          ( `fkSurvey`, `content`, `created`, `moderated` )
					                   VALUES ( {$fkSurvey}, '{$entry}', {$time}, true )" );
				}
			} else {
				$db->update( "UPDATE Entry 
				                 SET isDeleted = {$isDeleted} 
				               WHERE id = {$id} 
				                 AND fkSurvey = {$fkSurvey}" );
			}
		}
		return array();
	}
	
	public static function saveAdministrators( $fkSurvey, $args ) {
		$errors   = array();
		$fkSurvey = (int)$fkSurvey;
		$errors   = array_merge( $errors, self::syncUsers( $fkSurvey, $args ) );     // create/delete users, email about survey & password
		$errors   = array_merge( $errors, self::syncNewAdmins( $fkSurvey, $args ) ); // map existing users to survey for first time, email
		$errors   = array_merge( $errors, self::updateUserPermissions( $fkSurvey, $args ) ); // save all permissions (new and old admins)

		return $errors;
	}

	//===== Helper ============================================================
	private static function getTimeFromHuman( $human ) {
		$parts = explode( "/", $human );
		if( count( $parts ) != 3 ) return '';
		return mktime( 0, 0, 0, $parts[0], $parts[1], $parts[2] );
	}
	
	// Add new users and map them in so thewy don't get two emails
	private static function syncUsers( $fkSurvey, $args ) {
		$errors = array();
		$db     = Mysql::singleton();
		$sqlArr = array();
		$emails = array();
		foreach( $args AS $arg ) {
			$sqlArr[] = "'" . Mysql::escapeString( trim( $arg['email'] ) ) . "'";
			$emails[] = trim( $arg['email'] );
		}
		// Add New Users
		$sql      = implode( ', ', $sqlArr );
		$existing = (array)$db->selectColumn( "SELECT email FROM User WHERE email IN ( $sql )" );
		$toAdd    = array_diff( $emails, $existing );
		foreach( $toAdd AS $user ) {
			$id = Account_AccountLib::generateAccount( $user );
			$db->insert( "INSERT INTO UserSurveyMap ( `fkUser`, `fkSurvey` ) VALUES ( {$id}, {$fkSurvey} )" );
		}

		// Remove Missing Users
		$existing = $db->selectColumn( "SELECT U.email 
		                                  FROM User U 
		                            INNER JOIN UserSurveyMap USM ON USM.fkUser = U.id 
		                                 WHERE USM.fkSurvey = {$fkSurvey}" );
		$toDelete = array_diff( $existing, $emails );

		if( count( $toDelete ) > 0 ) {
			$sqlArr = array();
			foreach( $toDelete AS $email ) {
				$sqlArr[] = "'" . Mysql::escapeString( $email ) . "'";
			}
			$emailSql = implode( ", ", $sqlArr );
			$ids      = Mysql::singleton()->selectColumn( "SELECT id FROM User WHERE email IN ( {$emailSql} )" );
			$idSql    = implode( ", ", $ids );
			Mysql::singleton()->delete( "DELETE FROM UserSurveyMap WHERE fkSurvey = {$fkSurvey} AND fkUser IN ( $idSql )" );
		}
		return $errors;
	}
	// Process users that already existed but need to be mapped and emailed
	private	static function syncNewAdmins( $fkSurvey, $args ) {
		$errors = array();
		$db     = Mysql::singleton();

		$existingEmails = $db->selectColumn( "SELECT U.email 
		                                        FROM User U 
		                                  INNER JOIN UserSurveyMap USM ON USM.fkUser = U.id 
		                                       WHERE USM.fkSurvey = {$fkSurvey}" );
		$allEmails = array(); // all users in survey
		foreach( $args AS $arg ) {
			$allEmails[] = Mysql::escapeString( trim( $arg['email'] ) );
		}
		$tmp   = array_diff( $allEmails, $existingEmails );
		$toAdd = array();
		foreach( $tmp AS $email ) {
			$toAdd[] = "'" . $email . "'";
		}

		$sql      = implode( ", ", $toAdd );
		if( $sql != '' ) {
			$newUsers = $db->select( "SELECT U.id, U.email 
			                            FROM User U 
			                           WHERE U.email IN ( {$sql} )" );

			$domain = Utilities::getServerName();
			if( substr( $domain, 0, 4 ) == 'www.' ) {
				$domain = substr( $domain, 4 );
			}
			foreach( $newUsers AS $user ) {
				$id    = $user['id'];
				$email = $user['email'];
				$db->insert( "INSERT INTO UserSurveyMap ( `fkUser`, `fkSurvey` ) VALUES ( {$id}, {$fkSurvey} )" );
			
				$mailer = new Mailer();
				$mailer->setTo( $email );
				$mailer->setFrom( "noreply@" . $domain );
				$mailer->setSubject( "You have been added as an administrator at " . Utilities::getServerName() );
				$mailer->setBody( "You have been added as an administrator at " . Utilities::getServerName() . 
				                  "\r\n\r\nYou may log in to manage this survey, at " . Config::$baseUrl );
				$mailer->send();
			}
		}
		return $errors;
	}	

	// Update permissions for all admins (new and old)
	private static function updateUserPermissions( $fkSurvey, $admins ) {
		$errors = array();
		$sqlArr = array();
		$emails = array();
		foreach( $admins AS $admin ) {
			$sqlArr[] = "'" . Mysql::escapeString( trim( $admin['email'] ) ) . "'";
			$emails[] = trim( $admin['email'] );
		}
		$sql = implode( ', ', $sqlArr );
		$users = (array)Mysql::singleton()->select( "SELECT id, email FROM User WHERE email IN ( $sql )" );

		$index = array();
		foreach( $users AS $user ) {
			for( $i = 0; $i < count( $admins ); $i++ ) {
				if( trim( $user['email'] ) == trim( $admins[$i]['email'] ) ) {
					$admins[$i]['id'] = $user['id'];
				}
			}
		}
		
		foreach( $admins AS $admin ) {
			if( !isset( $admin['id'] ) ) throw new Exception( "There was an error setting permissions for the Administrators" );
			$fkUser = (int)$admin['id'];
			$gen 		= ( $admin['canModifyGeneral'] == 'true' 			? 1 : 0 );
			$sch 		= ( $admin['canSchedule'] == 'true' 					? 1 : 0 );
			$adm 		= ( $admin['canManageAdmins'] == 'true' 			? 1 : 0 );
			$par 		= ( $admin['canManageParticipants'] == 'true' ? 1 : 0 );
			$mod 		= ( $admin['canModerate'] == 'true' 					? 1 : 0 );
			$rep 		= ( $admin['canViewReports'] == 'true' 				? 1 : 0 );
			Mysql::singleton()->update( 
									 "UPDATE UserSurveyMap 
											 SET canModifyGeneral 			= {$gen},
													 canSchedule 						= {$sch},
													 canManageAdmins 				= {$adm},
													 canManageParticipants 	= {$par},
													 canModerate 						= {$mod},
													 canViewReports 				= {$rep}
										 WHERE fkUser 	= {$fkUser} 
											 AND fkSurvey = {$fkSurvey}" );
			
		}
		return $errors;
	}
	
}

?>