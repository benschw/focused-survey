<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US" lang="en-US">
  <head>
  	<title>Focused Survey - ${data/title}</title>
		<link rel="stylesheet" type="text/css" href="/media/styles/common.css" />
		<link rel="stylesheet" type="text/css" href="/media/styles/survey.css" />
		<link rel="stylesheet" type="text/css" href="/media/styles/public.common.css" />
		<script type="text/javascript" src="/media/js/mootools.js"></script>
		<script type="text/javascript" src="/media/js/mootools.plugins.js"></script>
		<script type="text/javascript" src="/media/js/survey/Phase1Survey.js"></script>
		<script type="text/javascript" src="/media/js/survey/Phase2Survey.js"></script>
		<script type="text/javascript" src="/media/js/survey/SurveyDriver.js"></script>
		<script tal:content="structure data/loadSurvey"></script>
  </head>
	<body>
    <div id="frame" tal:attributes="class data/macro">
			<noscript class="instructions">
				Please Enable Javascript and Refresh This Page To Continue
			</noscript>
			<metal:block use-macro="framework.tpl/${data/macro}" />
			<div id="footer">
				powered by <a title="benhschwartz.com" href="http://www.benhschwartz.com">benhschwartz.com</a>
				&nbsp;&nbsp;&nbsp;| &nbsp;&nbsp;&nbsp;<a href="/">Home</a>
			</div>
		</div>
	</body>
</html>

<metal:block define-macro="new">
	<div id="header">
		<h1 tal:content="data/title" />
	</div>
	<div id="subHeader1">
		<div id="subHeader2"></div>	
	</div>	
	<div id="panel">
		<p class="instructions">This Survey Has Not Yet Begun</p>
	</div>
</metal:block>

<metal:block define-macro="phase1">
	<div id="header">
		<h1><tal:block content="data/title" /> <span class="note">Phase I</span></h1>
	</div>
	<div id="subHeader1">
		<div id="subHeader2"></div>	
	</div>	
	<div id="panel">
		<div class="surveyDescription" tal:content="data/description" />
		<fieldset class="addEntry">
			<label for="entryField" class="note">New Entry</label>
			<textarea id="entryField" name="entry" />
			<img src="/media/images/add-big.png" id="addEntry" alt="Add" />
		</fieldset>
		<ul id="entryList">
		</ul>
	</div>
</metal:block>

<metal:block define-macro="phase2">
	<div id="header">
		<h1><tal:block content="data/title" /> <span class="note">Phase II</span></h1>
	</div>
	<div id="subHeader1">
		<div id="subHeader2"></div>	
	</div>	
	<div id="panel">
		<div class="surveyDescription" tal:content="data/description" />
		<ul id="entryList">
			<li tal:repeat="entry data/entries" class="entry rating">
				<div class="content" tal:content="entry/content" />
					<form class="phase2Survey" tal:attributes="id entry/id" >
						<fieldset class="rating">
							<input name="rating" type="radio" value="0" /> 
							<label>Strongly Disagree</label>
							<input name="rating" type="radio" value="25" /> 
							<label>Disagree</label>
							<input name="rating" type="radio" value="50" /> 
							<label>Neutral</label>
							<input name="rating" type="radio" value="75" /> 
							<label>Agree</label>
							<input name="rating" type="radio" value="100" /> 
							<label>Strongly Agree</label>
							<span class="noOpinion"></span>
							<input name="rating" type="radio" value="-1" checked="true" /> 
							<label>No Opinion</label>
						</fieldset>
					</form>
				</li>
			</ul>
			<input type="submit" name="submitRatings" id="submitRatings" value="Submit" />
		<div class="clear"></div>
	</div>
</metal:block>

<metal:block define-macro="phase25">
	<div id="header">
		<h1><tal:block content="data/title" /> <span class="note">Phase II</span></h1>
	</div>
	<div id="subHeader1">
		<div id="subHeader2"></div>	
	</div>	
	<div id="panel">
		<p class="instructions">Thank you for participating</p>
	</div>
</metal:block>

<metal:block define-macro="complete">
	<div id="header">
		<h1><tal:block content="data/title" /> <span class="note">Complete</span></h1>
	</div>
	<div id="subHeader1">
		<div id="subHeader2"></div>	
	</div>	
	<div id="panel">
		<p class="instructions">This Survey Is Already Complete</p>
	</div>
</metal:block>

<metal:block define-macro="notfound">
	<div id="header">
		<h1>Survey Not Found</h1>
	</div>
	<div id="subHeader1">
		<div id="subHeader2"></div>	
	</div>	
	<div id="panel">
	</div>
</metal:block>
