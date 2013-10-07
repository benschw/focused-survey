<?php
require_once "../../../../lib/Config.class.inc";

class RemoteCall {

	public $methodTable;

	public function call( $argObject ) { 
	  $args = $argObject['args'];
	  $args['fw_request'] = $argObject['module'] . '.' . $argObject['classname'] . '.' . $argObject['method'] . '.Data';

    Config::initFramework();
    Config::addModuleToPath( 'Base' );
    Config::addModuleToPath( 'ViralVideo' );

    try {
      $controller = new Controller( $args );

      if( $controller->authorize() && $controller->authenticate() ) {
        if( $controller->run() ) { 
          return $controller->render();
        }
      }

    } catch( Exception $e ) {
      $response = new ResponseTO();
      $response->status   = 1;
      $response->results  = false;
      $response->debug    = get_class( $e ) . ": " . $e->getMessage() . "\n\n" . $e->getTraceAsString();
      return $response;
    }
	}

}

?>