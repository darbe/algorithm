import urllib2
import cookielib
class LoginHelper:
	def __init__ (self,username,passwd,path):
		self.username = username
		self.passwd = passwd
		self.path = path
		self.cookie = cookielib.LWPCookieJar()
		self.opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(self.cookie))
		urllib2.install_opener(self.opener)
