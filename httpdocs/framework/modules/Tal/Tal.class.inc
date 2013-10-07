<?php

class Tal_Tal {
	
	private $template;
	private $data;
	private $scope;
	
	public function __construct( $template, $data = array(), $scope = 'application' ) {
		$this->template 	= $template;
		$this->data 			= $data;
		$this->scope 			= $scope;
    require_once Config::$frameworkvendorPath . 'PHPTAL/PHPTAL.php';
	}

	public function getRendered() {
		$tplPath = ( $this->scope == 'framework' ? Config::$frameworkTemplatePath : Config::$applicationTemplatePath );
		$template = new PHPTAL( $tplPath . $this->template );

		$template->frameworkTemplatePath = Config::$frameworkTemplatePath;
		$template->templatePath = Config::$applicationTemplatePath;
		$template->mediaPath 		= Config::$mediaPath;
		$template->data 				= $this->data;

		return $template->execute();
	}
	
	public function render() {
		try {
			
      print $this->getRendered();
			return true;

		} catch( Exception $e ) {
			throw( $e );
		}
	}

}

?>
