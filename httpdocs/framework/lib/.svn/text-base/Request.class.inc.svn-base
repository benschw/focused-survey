<?php

class Request {

	private $args;					// full request resource (e.g. $_GET array)

	private $module;
	private $method;

	private $driverInstance;
	private $moduleResult;
	
	public function __construct( $args ) {
		try {
			Mysql::singleton(); // so that mysql_real_escape_string() will work

		  $this->args = $args;
			if( isset( $args['fw_request'] ) ) {
				$requestArr 	= explode( ".", $args['fw_request'] );

				$this->module = ( isset( $requestArr[0] ) ? $requestArr[0] : null );
				$this->class 	= ( isset( $requestArr[1] ) ? $requestArr[1] : $this->module );
				$this->method = ( isset( $requestArr[2] ) ? $requestArr[2] : 'main' );
			} else {
				throw new RequestException( "fw_request is not set. Cannot continue" );
			}
		} catch( Exception $e ) {
			$this->processException( $e, __METHOD__ );
		}
	}

	public function authenticate() {
    return Auth::authenticate( $this->module, $this->class, $this->method, $this->args );
	}
	public function authorize() {
    return Auth::authorize( $this->module, $this->class, $this->method, $this->args );
	}

	public function run() {
		try {
			Config::addModuleToPath( 'application', $this->module );

			$className = "{$this->module}_{$this->class}";
			$this->driverInstance = new $className( $this->args );

			if( method_exists( $this->driverInstance, $this->method ) ) {
	  		$this->moduleResult = $this->driverInstance->{$this->method}( $this->args );
			} else {
			  throw new RequestException( "Method '{$this->method}' does not exist" );
			}
		} catch( Exception $e ) {
			$this->processException( $e, __METHOD__ );
			return false;
		}
		return true;
	}

	public function render() {
		try {
			if( !is_object( $this->moduleResult ) ) {
				throw new RenderingEngineException( "Module Result is Not an Object" );
			}
			return $this->moduleResult->render();

		} catch( Exception $e ) {
			$this->processException( $e, __METHOD__ );
		}
	}	
	
	private function processException( Exception $e, $method ) {
		print "<pre>" . $e . "</pre>";
	}
}

?>