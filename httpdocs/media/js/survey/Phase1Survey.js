var Phase1Survey = new Class({
	fkSurvey 		: null,
	refresher 	: null,
	lastUpdate 	: 0,
	
	pollInterval 	: 1000 * 10,
	pollTimeout 	: 1000 * 60 * 60,
	idlePolls 		: 0,
	idleMessage		: "You have been idle for a while. Please refresh your browser to continue loading entries dynamically.",
	
	initialize: function( fkSurvey ) {  
		this.fkSurvey = fkSurvey;
		
		this.loadNewEntries();
		this.refresher = function() {
			this.idlePolls++;
			if( this.idlePolls * this.pollInterval > ( this.pollTimeout ) ) {
				alert( this.idleMessage );
				$clear( this.refresher );
				return;
			}
			this.loadNewEntries();
		}.periodical( this.pollInterval, this)

		if( $("addEntry") ) {
			$('addEntry').addEvent( 'click', function(e) {
				this.idlePolls = 0;
				this.addEntry();
			}.bind(this));
		}
	},	

	loadNewEntries : function() {
		var request = new Request.JSON({
			'url' : '/fw.Survey.PublicSurvey.getNewEntries', 
			'data' : {	id : this.fkSurvey, time : this.lastUpdate },
			onSuccess: function( response ) {
				if( response.result ) {
					this.lastUpdate = response.time;
					response.entries.each( function( elem ) {
						$('entryList').innerHTML = elem + $('entryList').innerHTML;
					});
					$$('#entryList li.new').each( function(elem) {

						var myEffect = new Fx.Morph(elem, {duration: 500});
						myEffect.start({
						    'background-color': '#FFFFFF'
						}).chain(function(){
							elem.removeClass( 'new' );						
						});
					}.bind(this));
				} else {
					alert( response.message );
				}
			}.bind(this)
		}).send();
	},

	addEntry : function() {
		var entry = $('entryField').value;
		var request = new Request.JSON({
			'url' : '/fw.Survey.PublicSurvey.addEntry', 
			'data' : {	'id' : this.fkSurvey, 'newEntry' : entry },
			onSuccess: function( response ) {
				if( response.result ) {
					$('entryField').value = '';
					this.loadNewEntries();
				} else {
					alert( response.message );
				}
			}.bind(this)
		}).send();
	}
	
});