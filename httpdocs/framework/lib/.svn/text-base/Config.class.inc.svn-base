<?php

class Config {
	
	public static $debug = true;
	
	public static $paths = array();
	public static $frameworkModules 	= array();
	public static $applicationModules = array();
	
	public static $settings;
  
	public static $baseUrl;
	public static $mediaUrl;
	
	
	public static $basePath;

	public static $frameworkPath;
	public static $frameworkLibPath;
	public static $frameworkModulePath;
	public static $frameworkvendorPath;
	public static $frameworkTemplatePath;
	public static $viewPath;

	public static $applicationPath;
	public static $applicationLibPath;
	public static $applicationModulePath;
	public static $applicationTemplatePath;
	public static $mediaPath;

	public static $dbEnabled;
	public static $dbLogin;
	public static $dbPassword;
	public static $dbDatabase;
	public static $dbServer;

	public static function initFramework() {
		date_default_timezone_set('America/New_York');
		if( self::$debug ) {
			error_reporting( E_ALL | E_STRICT );  // Error Reporting
			ini_set( "display_errors" , 1 );    	// Display Errors
		}
		
    self::$basePath = dirname( dirname( dirname( __FILE__ ) ) ).'/';

	  self::$settings = parse_ini_file( self::$basePath."config/config.ini", true );

    self::$frameworkPath 		  			= self::$basePath . 'framework/';
    self::$frameworkLibPath	  			= self::$basePath . 'framework/lib/';
    self::$frameworkModulePath			= self::$basePath . 'framework/modules/';
    self::$frameworkvendorPath			= self::$basePath . 'framework/vendor/';
    self::$viewPath           			= self::$basePath . 'framework/view/';
    self::$frameworkTemplatePath		= self::$basePath . 'framework/templates/';
	  
    self::$applicationPath					= self::$basePath . 'application/';
    self::$applicationLibPath				= self::$basePath . 'application/lib/';
    self::$applicationModulePath		= self::$basePath . 'application/modules/';
    self::$applicationTemplatePath	= self::$basePath . 'media/templates/';

    self::$mediaPath          			= self::$basePath . 'media/';

		require_once self::$frameworkLibPath	. "Utilities.class.inc";
		require_once self::$frameworkPath    	. "Exceptions.inc";
		require_once self::$applicationPath  	. "Exceptions.inc";
			
		spl_autoload_register( array( 'Utilities', 'autoloadClass' ) );
		set_error_handler( array( 'Utilities', 'customErrorHandler' ) ); 
 		self::$baseUrl 	= Utilities::getProtocol() . '://' . Utilities::getServerName() . '/';
		self::$mediaUrl = self::$baseUrl . 'media/';

		self::$paths[] = self::$frameworkLibPath;
		self::$paths[] = self::$applicationLibPath;
	}

	public static function addModuleToPath( $scope, $module ) {
		switch( $scope ) {
			case 'framework' 		: self::$frameworkModules[] = $module;		break;
			case 'application' 	: self::$applicationModules[] = $module;	break;
			default : throw new ApplicationException( "Unknown Scope: {$scope}" );
		}
	}

}

?>