<?php
Config::addModuleToPath( 'framework', 'JSON' );

class Account_Authenticated {

	public function isTemporaryLogin( $args ) {
		return new JSON_JSON( array( "result" => (bool)Session::singleton()->temporary ) );
	}

	public function clearTemporaryPassword( $args ) {
		return new JSON_JSON( array( "result" => Account_AccountLib::clearTemporaryPassword( Session::singleton()->loginID ) ) );
	}

	public function changePassword( $args ) {
		if( !isset( $args['password'] ) || !isset( $args['password2'] ) ) {
			return new JSON_JSON( array( "result" => false, 'message' => "Please complete all fields" ) );
		}
		list( $result, $message ) = Account_AccountLib::changePassword( Session::singleton()->loginID, $args['password'], $args['password2'] );
		if( $result ) {
			Session::singleton()->temporary = false;
		}
		return new JSON_JSON( array( "result" => $result, 'message' => $message ) );
	}

	public function logout( $args ) {
		Account_AccountLib::logout();
		return new JSON_JSON( array( "result" => (bool)Session::singleton()->loginID ) );
	}
	
}

?>