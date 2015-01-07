class UserMailer < ActionMailer::Base
  @@pdf_name = 'imta2015-cfp-2.pdf'
  @@pdf_path = Rails.root.to_s + "/" + @@pdf_name
  default from: "\"DCC RAS\" <lcmi@ccas.ru>"

  def imta_second_call(user_mail)
  	pdf = File.read(@@pdf_path, mode: "rb") 
  	#pdf = render_to_string :pdf => @@pdf_name
    attachments[@@pdf_name] = pdf if pdf.present?
    mail(to: user_mail, subject: 'IMTA-5 2015: 2nd Call for Participation')
  end
end
