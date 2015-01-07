class SendmailController < ApplicationController
	@@arr = ["vichugunov@gmail.com"]
	
	def deliver(user_mail)
		UserMailer.imta_second_call(user_mail).deliver
	end

	def mass_delivery
		@@arr.each { |a| 
			deliver(a) 
		}
	end
end
