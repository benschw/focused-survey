<?php

class JSON_JSON {
	
	private $data;
	
	public function __construct( $data ) {
		$this->data = $data;
	}
	
	public function render() {
		print json_encode( $this->data );
	}


}

?>
