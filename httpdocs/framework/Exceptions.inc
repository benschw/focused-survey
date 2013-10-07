<?php

// All Exceptions extend FrameworkException
class FrameworkException extends Exception {}

  // General Framework Exceptions
  class RequestException extends FrameworkException {}
  class UserInputException extends FrameworkException {}
  class AuthorizationException extends FrameworkException {}
  class AuthenticationException extends FrameworkException {}

  // Application Exceptions (application level exceptions extend this)
  class ApplicationException extends FrameworkException {}
  class ProxyException extends ApplicationException {}
  class MailerException extends ApplicationException {}

  class PanelException extends ApplicationException {}

  // Rendering Engine Exceptions
  class RenderingEngineException extends FrameworkException {}




?>