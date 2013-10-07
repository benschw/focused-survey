var AutoSize = {

	initialize: function() {
		this.redraw();
		window.addEvent( 'resize', function(e) {
			this.redraw();
		}.bind(this));
	},
	
	redraw : function() {
		var height = window.getSize().y;
		if( $('surveyToolsPanel') ) {
			$('surveyToolsPanel').setStyle( 'height', height - 96 + "px" );
		}
		if( $('listComponent') ) {
			$('listComponent').setStyle( 'height', height - 160 + "px" );
		}
		if( $('surveyToolsInnerWrapper') ) {
			$('surveyToolsInnerWrapper').setStyle( "height", height - 213 + "px" );
		}
	}
	
};
