<?php

class Auth {
	

	public static function authenticate( $module, $class, $method, $args ) {
		return true;
	}

	public static function authorize( $module, $class, $method, $args ) {
		if( $module == 'Account' && $class == 'Public' ) {
			return true;
		} else if( $module == 'Survey' && $class == 'PublicSurvey' ) {
			return true;
		} else if( $module == 'UI' && $class == 'Public' ) {
			return true;
		} else {
			return isset( Session::singleton()->loginID );
		}
	}

}

?>