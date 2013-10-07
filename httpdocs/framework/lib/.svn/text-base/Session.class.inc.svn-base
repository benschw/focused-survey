<?php
/*  Session singleton class
 */
class Session {
	
	protected static $instance;
	const NAME_SPACE = 'default';
	
	public function __construct() {
		if( !isset( $_SESSION ) ) {
			if( isset( $_GET['PHPSESSID'] ) ) {
				session_id($_GET['PHPSESSID']);
			}
			session_start();
		}
	}
  public static function singleton() {
		if (!isset(self::$instance)) {
			$className = __CLASS__;
			self::$instance = new $className;
		}
		return self::$instance;
  }

  public function __clone() {
		throw( new Exception( "cannot clone object, it is singleton" ) );
  }

	//==========================================================================
	// Public
	//==========================================================================

	public function __set( $key, $val ) { // $session->key = $val;
		return( $_SESSION[self::NAME_SPACE][$key] = $val );
	}
	public function __get( $key ) {
		if( isset( $_SESSION[self::NAME_SPACE][$key] ) )
			return $_SESSION[self::NAME_SPACE][$key];
	}

	public function __isset( $key ) {
		return isset( $_SESSION[self::NAME_SPACE][$key] );
	}

	public function __unset( $key ) {
		unset( $_SESSION[self::NAME_SPACE][$key] );
	}

}
?>