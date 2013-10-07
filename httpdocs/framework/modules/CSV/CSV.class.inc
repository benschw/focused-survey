<?php

class CSV_CSV {
	
	private $title;
	private $data;
	private $scope;
	
	public function __construct( $title, $data = array(), $scope = 'application' ) {
		$this->title = $title;
		$this->data  = $data;
		$this->scope = $scope;
	}

	public function getRendered() {
		$html     = '';
		$doHeader = true;

		foreach( $this->data AS $row ) {
			if( $doHeader ) {
				$html .= $this->getRow( array_keys( $row ) );
				$doHeader = false;
			}
			$html .= $this->getRow( array_values( $row ) );
		}
		return $html;
	}
	public function getRow( $row ) {
		for( $i = 0; $i < count( $row ); $i++ ) {
			$row[$i] = $this->cleanupField( $row[$i] );
		}
		return implode( ',', $row ) . "\n" ;
	}
	public function render() {
		try {
			$fname       = $this->title;
			$mimetype    = "application";
			$mimesubtype = "unknown";

			// $fp = fopen($fname,"r");
			header("Content-type: $mimetype/$mimesubtype");
			header(sprintf('Content-disposition: attachment; filename="%s"', basename($fname)));
			header("Expires: 0");
			header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
			header("Pragma: public");

			print $this->getRendered();
			return true;

		} catch( Exception $e ) {
			throw( $e );
		}
	}

	protected function cleanupField( $field ) {
		$field = preg_replace( '/\r\n/', ' ', $field );
		$field = preg_replace( '/"/', '""', $field );
		if( is_int( strpos( $field, ',' ) ) ) {
			$field = '"' . $field . '"';
		}

		return $field;
	}
}

?>