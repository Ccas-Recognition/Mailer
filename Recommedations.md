To use for server (development):  

config.action_mailer.perform_deliveries = true 
  config.action_mailer.raise_delivery_errors = true
  config.action_mailer.delivery_method = :smtp
  config.action_mailer.smtp_settings = {
   :address              => "smtp.live.com",
   :port                 => 587,
   :enable_starttls_auto => true,
   :user_name            => 'noreply@example.com',
   :password             => 'password',
   :domain               => 'example.com',
   :authentication       => 'plain'
 }

Also can check this:

3
down vote
Do you have

config.action_mailer.default_url_options = { 
  :host => 'YOUR_HOST_NAME_HERE'
   }
defined in application.rb or production.rb? It should be set to your domain name. I've found that some servers will reject mail without an explicitly defined hostname.

---


3
down vote
Do you have

config.action_mailer.default_url_options = { 
  :host => 'YOUR_HOST_NAME_HERE'
   }
defined in application.rb or production.rb? It should be set to your domain name. I've found that some servers will reject mail without an explicitly defined hostname.
