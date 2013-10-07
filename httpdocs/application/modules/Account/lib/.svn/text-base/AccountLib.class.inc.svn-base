<?php

class Account_AccountLib {
	
	public static function generateAccount( $email ) {
		if( !TypeUtil::isEmail( $email ) ) throw new Exception( "Bad Email" );
		$email 		= Mysql::escapeString( trim( $email ) );
		$password = substr( md5( $email . time() ), 0, 8 );
		$encoded	= Mysql::escapeString( sha1( $password ) );

		$loginAvailable = !(bool)Mysql::singleton()->count( "SELECT count(*) FROM User WHERE email = '{$email}'" );
		if( !$loginAvailable ) throw new Exception( "There is already an account for that email" );
		
		$newID = Mysql::singleton()->insert( "INSERT INTO User SET email = '{$email}', tmpPassword = '{$encoded}'" );

		$domain = Utilities::getServerName();
		if( substr( $domain, 0, 4 ) == 'www.' ) {
			$domain = substr( $domain, 4 );
		}
		$mailer = new Mailer();
		$mailer->setTo( $email );
		$mailer->setFrom( "noreply@" . $domain );
		$mailer->setSubject( "You have been added as an administrator at " . Utilities::getServerName() );
		$mailer->setBody( "Your temporary password is:\r\n\r\n{$password}"
										 ."\r\n\r\nPlease log in to change it.\r\n\r\n" . Config::$baseUrl );
		$mailer->send();
		return $newID;
	}

	public static function createAccount( $email, $password, $password2 ) {
		if( trim( $email ) == '' || trim( $password ) == '' ) return array( false, "Please insure that all fields have been filled out" );
		$email 			= Mysql::escapeString( trim( $email ) );
		$password 	= Mysql::escapeString( sha1( trim( $password ) ) );
		$password2 	= Mysql::escapeString( sha1( trim( $password2 ) ) );

		if( !TypeUtil::isEmail( $email ) ) return array( false, "Please supply a valid email" );
		if( $password != $password2 ) return array( false, "Please insure that your passwords match" );

		$loginAvailable = !(bool)Mysql::singleton()->count( "SELECT count(*) FROM User WHERE email = '{$email}'" );
		if( !$loginAvailable ) return array( false, "There is already an account for that email" );
		
		$id = Mysql::singleton()->insert( "INSERT INTO User SET email = '{$email}', password = '{$password}'" );
		return array( true, $id );
	}

	public static function changePassword( $loginID, $password, $password2 ) {
		if( $password == '' ) return array( false, "Please insure that all fields have been filled out" );
		$loginID 		= (int)$loginID;
		$password 	= Mysql::escapeString( sha1( trim( $password ) ) );
		$password2 	= Mysql::escapeString( sha1( trim( $password2 ) ) );
		if( $password != $password2 ) return array( false, "Please insure that your passwords match" );
		Mysql::singleton()->update( "UPDATE User SET password = '{$password}', tmpPassword = '' WHERE id = {$loginID}" );
		return array( true, "" );
	}

	public static function login( $email, $password ) {
		$email 		= Mysql::escapeString( trim( $email ) );
		$password = Mysql::escapeString( sha1( trim( $password ) ) );
		$id = Mysql::singleton()->selectField( "SELECT id FROM User WHERE email = '{$email}' AND password = '{$password}'" );
		if( $id ) {
			$s = Session::singleton();
			$s->loginID = $id;
			$s->email = $email;
			$s->temporary = false;
			return true;
		} else {
			$id = Mysql::singleton()->selectField( "SELECT id FROM User WHERE email = '{$email}' AND tmpPassword = '{$password}'" );
			if( $id ) {
				$s = Session::singleton();
				$s->loginID = $id;
				$s->email = $email;
				$s->temporary = true;
				return true;
			}
			return false;
		}
		return false;
	}

	public static function resetPassword( $email ) {	
		$email = Mysql::escapeString( trim( $email ) );
		if( (bool)Mysql::singleton()->count( "SELECT count(*) FROM User WHERE email = '{$email}'" ) ) {
			$password = substr( md5( $email . time() ), 0, 8 );
			$encPassword = sha1( $password );
			Mysql::singleton()->update( "UPDATE User SET tmpPassword = '{$encPassword}' WHERE email = '{$email}'" );
			$domain = Utilities::getServerName();
			if( substr( $domain, 0, 4 ) == 'www.' ) {
				$domain = substr( $domain, 4 );
			}
			$mailer = new Mailer();
			$mailer->setTo( $email );
			$mailer->setFrom( "noreply@" . $domain );
			$mailer->setSubject( "The temporary password you requested" );
			$mailer->setBody( "Your Password has been reset to:\r\n\r\n{$password}\r\n\r\n" . Config::$baseUrl );
			try {
				$mailer->send();
			} catch( MailerException $e ) {
				return false;
			}
			return true;
		}
		return false;
	}

	public static function clearTemporaryPassword( $loginID ) {
		$loginID = (int)$loginID;
		return Mysql::singleton()->update( "UPDATE User SET tmpPassword = '' WHERE id = {$loginID}" );
	}
	
	public static function logout() {
		$s = Session::singleton();
		unset( $s->loginID );
		unset( $s->email );
		unset( $s->temporary );
	}
	
	//==========================================================================
	
}

?>