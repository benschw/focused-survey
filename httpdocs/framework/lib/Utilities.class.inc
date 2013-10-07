<?php

class Utilities {

// Framework Related ===========================================================

	public static function customErrorHandler( $num, $str, $file, $line ) {
	  $err  = "PHP Error #: \t{$num}\n";
	  $err .= "String: \t{$str}\n";
	  $err .= "File: \t\t{$file}\n";
	  $err .= "Line: \t\t{$line}\n";

		throw new Exception( $err );
	}

	public static function autoloadClass( $className ) {
		$moduleProfile = array( '', 'lib/', 'inc/', 'data/', 'ui/', 'adapters/' );
		$path 	= array_unique( Config::$paths );
		$length = count( $path );

		if( strpos( $className, '_' ) !== false ) {
			$parts = explode( '_', $className );
			$modulePathes = array( Config::$frameworkModulePath		=> Config::$frameworkModules, 
														 Config::$applicationModulePath	=> Config::$applicationModules );

			foreach( $modulePathes AS $basePath => $modules ) {
				if( in_array( $parts[0], $modules ) ) {
					foreach( $moduleProfile AS $folder ) {
						$testPath = $basePath . $parts[0] . "/{$folder}" . $parts[1] . '.class.inc';
						if( is_file( $testPath ) ) {
							require_once( $testPath );
							return true;
						}
					}
				}
			}
		}
		for( $i = $length - 1; $i >= 0; $i-- ) {
			$testPath = $path[$i] . $className . '.class.inc';
			if( is_file( $testPath ) ) {
				require_once( $testPath );
				return true;
			}
		}
		return false;
	}

	public static function debug( $arr, $message = false, $properties = false ) {
		if( Config::$debug ) {
			if( $message )
				print "<fieldset>{$message}";

			print "<fieldset><pre>";
			
			if( $properties ) {
				print_r( $properties );
			}

			if( $arr instanceof Exception ) {
				echo $arr->getMessage() . "\n\n" . $arr;
			} else if( is_array( $arr ) || is_object( $arr ) ) {
				print_r( $arr );
			} else {
				print $arr;
			}
			print '</pre></fieldset>';
			if( $message )
				print "</fieldset>";
		}
	}

	public static function mysqlEscape( $msg ) {
		return mysql_real_escape_string( $msg );
	}

  public static function benchmarkTime( $startTime, $endTime = null ) {
    if( is_null( $endTime ) ) {
      $endTime = microtime();
    }
    list( $start_usec, $start_sec ) = explode( " ", $startTime );
    list( $end_usec, $end_sec )     = explode( " ", $endTime );
    $diff_sec   = (int)$end_sec    - (int)$start_sec;
    $diff_usec  = (float)$end_usec - (float)$start_usec;
    return (float)$diff_sec + (float)$diff_usec;
  }


// Config Help =================================================================
	public static function getServerName() {
		if( isset( $_SERVER['SERVER_NAME'] ) ) {
			return $_SERVER['SERVER_NAME'];
		} else if( isset( $_SERVER['HOSTNAME'] ) ) {
			return $_SERVER['HOSTNAME'];
		} else if( isset( $_SERVER['HTTP_HOST'] ) ) {
			return $_SERVER['HTTP_HOST'];
		} else if( isset( $_SERVER['SERVER_ADDR'] ) ) {
			return $_SERVER['SERVER_ADDR'];
		} else {
			return 'localhost';
		}
	}

	public static function getProtocol() {
		return ( isset( $_SERVER['HTTPS'] ) && $_SERVER['HTTPS'] == 'on' ? 'https' : 'http' );
	}
 }


?>	