var Phase2Survey = new Class({
	fkSurvey : null,
	
	initialize: function( fkSurvey ) {  
		this.fkSurvey = fkSurvey;
		this.initSubmit();
	},	
	
	initSubmit : function() {
		if( $("submitRatings") ) {
			$('submitRatings').addEvent( 'click', function(e) {
				this.submitForm();
			}.bind(this));
		}
	},

	submitForm : function() {
		var values = {};
		$$( "form.phase2Survey" ).each( function( form ) {
			values[form.id] = null;
			form.getElements('input[name=rating]').each( function( radio ) {
				if( radio.checked ) {
					values[form.id] = radio.value;
				}
			});
		});
		
		var request = new Request.JSON({
			'url' : '/fw.Survey.PublicSurvey.submitRatings', 
			'data' : { 'id' : this.fkSurvey, 'values' : values },
			onSuccess: function( response ) {
				if( response.result ) {
					var myCookie = Cookie.write(this.fkSurvey, 'submitted', {duration: 60});
					location.reload(true);
				} else {
					alert( response.message );
				}
			}.bind(this)
		}).send();
	}
	
});