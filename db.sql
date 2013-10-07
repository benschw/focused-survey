CREATE TABLE User ( 
	id int(10) auto_increment, 
	email varchar(255), 
	firstName varchar(255), 
	lastName varchar(255), 
	password varchar(255), 
	tmpPassword varchar(255), 
	PRIMARY KEY( id ) 
);

CREATE TABLE Survey (
	id int(10) auto_increment,
	title varchar(255),
	created int(10),
	phase1Description text,
	phase2Description text,
	phase1Subject varchar(255),
	phase2Subject varchar(255),
	phase1Body text,
	phase2Body text,
	scheduleType ENUM( 'schedule', 'toggle' ) DEFAULT 'toggle',
	phase1Start int(10),
	phase2Start int(10),
	end int(10),
	
	emailState int(2) DEFAULT 0,
	toggleState ENUM( 'new', 'phase1', 'phase2', 'complete' ) DEFAULT 'new',
	PRIMARY KEY( id ) 
);


CREATE TABLE UserSurveyMap (
	fkUser int(10),
	fkSurvey int(10),
	canModifyGeneral bool DEFAULT TRUE,
	canSchedule bool DEFAULT TRUE,
	canManageAdmins bool DEFAULT TRUE,
	canManageParticipants bool DEFAULT TRUE,
	canModerate bool DEFAULT TRUE,
	canViewReports bool DEFAULT TRUE,
	KEY fkUser_fkSurvey_idx ( fkUser, fkSurvey )
);

CREATE TABLE Participant (
	id int(10) auto_increment,
	fkSurvey int(10),
	email varchar(255),
	PRIMARY KEY ( id )
);

CREATE TABLE Entry (
	id int(10) auto_increment,
	fkSurvey int(10),
	isDeleted bool DEFAULT FALSE,
	moderated bool DEFAULT FALSE,
	content text,
	created int(10),
	timesRated int(10),
	ratingTotal int(10),	
	PRIMARY KEY ( id )
);

CREATE TABLE EntryResponse (
	id int(10) auto_increment,
	fkEntry int(10),
	rating int(10),
	time int(10),
	PRIMARY KEY ( id )
);
	
