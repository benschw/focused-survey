<?php
Config::addModuleToPath( 'framework', 'JSON' );
Config::addModuleToPath( 'framework', 'Tal' );

class Account_Public {

	//==========================================================================
	// Load
	//==========================================================================
	public function getLogin( $args ) {
		return new Tal_Tal( 'login/login.panel.tpl' );
	}
	public function getResetPassword( $args ) {
		$login = ( isset( $args['login'] ) ? $args['login'] : '' );
		return new Tal_Tal( 'login/reset.password.panel.tpl', array( 'login' => $login ) );
	}
	public function getNewAccount( $args ) {
		return new Tal_Tal( 'login/new.account.panel.tpl' );
	}
	public function getForcePasswordChange( $args ) {		
		return new Tal_Tal( 'login/force.password.change.tpl' );
	}

	//==========================================================================
	// Action Responses
	//==========================================================================
	public function getAddCreateSuccess( $args ) {
		return new Tal_Tal( 'login/new.account.success.panel.tpl' );
	}
	public function getResetResponse( $args ) {
		return new Tal_Tal( 'login/reset.response.panel.tpl' );
	}

	//==========================================================================
	// Actions
	//==========================================================================
	public function addAccount( $args ) {
		if( !isset( $args['email'] ) || !isset( $args['password'] ) || !isset( $args['password2'] ) ) {
			return new JSON_JSON( array( "result" => false, 'message' => "Please complete all fields" ) );
		}
		list( $result, $message ) = Account_AccountLib::createAccount( $args['email'], $args['password'], $args['password2'] );
		if( $result ) {
			$result = Account_AccountLib::login( $args['email'], $args['password'] );
		}
		return new JSON_JSON( array( "result" => $result, 'message' => $message ) );
	}

	public function login( $args ) {
		if( !isset( $args['email'] ) || !isset( $args['password'] ) ) {
			return new JSON_JSON( array( "result" => false ) );
		}
		$result = Account_AccountLib::login( $args['email'], $args['password'] );
		return new JSON_JSON( array( "result" => (bool)$result, 'isTemporary' => (bool)Session::singleton()->temporary ) );
	}

	public function resetPassword( $args ) { // email out a "temporary" password
		if( !isset( $args['email'] ) ) {
			return new JSON_JSON( array( "result" => false ) );
		}
		$result = Account_AccountLib::resetPassword( $args['email'] );
		return new JSON_JSON( array( "result" => (bool)$result ) );
	}

}

?>