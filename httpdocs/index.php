<?php
date_default_timezone_set( 'America/Los_Angeles' );

require_once "framework/lib/Config.class.inc";

Config::initFramework();

$controller = new Request( $_REQUEST );
if( $controller->authenticate() && $controller->authorize() ) {
  if( $controller->run() ) {
    $controller->render();
  }
} else {
	header( "Location: /?notLoggedIn=true" );
}
