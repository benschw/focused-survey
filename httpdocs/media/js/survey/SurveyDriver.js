var SurveyDriver = new Class({
  
	initialize: function( fkSurvey, status ) {  
		this.fkSurvey = fkSurvey;
		
		if( status == 1 ) {
			new Phase1Survey( fkSurvey );
		} else if( status == 2 ) {
			new Phase2Survey( fkSurvey );
		}
	}

});
