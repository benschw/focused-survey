<?php

class NameLib {

	public static function getNewName( $names, $base ) {

		if( $names )
			sort( $names );
		else
			$names = array();

		for( $i = 1; $i <= ( count( $names ) + 1 ); $i++ ) {
			$test = $base . ( $i == 1 ? "" : " {$i}" );
			if( !in_array( $test, $names ) ) {
				return( $test );
			}
		}

		return $base;
	}

	public static function getCopyName( $names, $base ) {
		$newBase = $base;
		$nameArr = explode( " ", $base );

		if( $nameArr[ count( $nameArr ) - 1 ] == 'copy' ) {

			array_pop( $nameArr );
			$newBase = implode( " ", $nameArr );

		} else if( $nameArr[ count( $nameArr ) - 2 ] == 'copy' ) {

			array_pop( $nameArr );
			array_pop( $nameArr );
			$newBase = implode( " ", $nameArr );

		}
		$tryForMain = NameLib::getNewName( $names, $newBase );
		if( $tryForMain == $newBase )
			return $newBase;
		else
			return NameLib::getNewName( $names, $newBase . ' copy' );
	}

	public static function getCleanFileName( $destPath, $desiredFileName ) {
		if( !is_dir( $destPath ) ) { throw new Exception( "directory to create file in does not exist" ); }
		if( !is_writable( $destPath ) ) { throw new Exception( "directory to create file in is not writable" ); }
		$parts 			= explode( '.', $desiredFileName );
		$extension 	= strtolower( array_pop( $parts ) );
		$baseName 	= preg_replace( '/\s+/', "-", implode( '.', $parts ) );
		$baseName 	= preg_replace( "/[^a-z0-9\-]/i", "", $baseName );

		$i = 0;
		
		do {
			if( !is_file( $destPath . $baseName . ( $i == 0 ? '' : $i ) . ".{$extension}" ) ) {
				return $baseName . ( $i == 0 ? '' : $i ) . ".{$extension}";
			}
		} while( ++$i && ( $i < 100 ) );

		throw new Exception( "Infinite Loop Detected while trying to find a unique file name" );
	}

}

?>