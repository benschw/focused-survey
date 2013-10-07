<?php


class ViewData {

	private $type;
	private $data;

	private $parameters;

	public function __construct( $engine = 'Void', $data = null ) {
		if( !is_file( Config::$viewPath . "{$engine}/{$engine}.class.inc" ) ) {
			throw new FrameworkException( "Rendering Engine: '{$engine}' not found." );
		}
		$this->engine = $engine;
		$this->data = $data;
	}

	public function getEngine() { return $this->engine; }
	public function getData() { return $this->data; }
	
	public function setParameter( $key, $val ) {
		$this->parameters[$key] = $val;
	}
	public function getParameter( $key ) {
		return $this->parameters[$key];
	}
	public function isParameterSet( $key ) {
		return isset( $this->parameters[$key] );
	}

}


?>