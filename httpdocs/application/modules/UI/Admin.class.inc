<?php

Config::addModuleToPath( 'framework', 'Tal' );
Config::addModuleToPath( 'application', 'Account' );

class UI_Admin {

	public function loadAdmin( $args ) {
		Account_AccountLib::clearTemporaryPassword(Session::singleton()->loginID);
		return new Tal_Tal('home/home.tpl');
	}
	

}
