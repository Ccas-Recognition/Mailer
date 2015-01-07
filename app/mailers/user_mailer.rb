class UserMailer < ActionMailer::Base
  default from: "\"DCC RAS\" <lcmi@ccas.ru>"

  def imta_first_call(user_mail)
  	attachments['imta2015-cfp-1.pdf'] = File.read('imta2015-cfp-1.pdf');
    mail(to: user_mail, subject: 'IMTA-5 2015: 1st Call for Participation')
  end
end
