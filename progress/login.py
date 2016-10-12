import urllib
import http.cookiejar
class LoginHelper:
	def __init__ (self,username,passwd,path):
		self.username = username
		self.passwd = passwd
		self.path = path
		self.cookie = cookielib.LWPCookieJar()
		self.opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(self.cookie))
		urllib2.install_opener(self.opener)

	def login(self):
		data = {
			'email' : self.username
			'password' : self.password
		}
		loginUrl = 'http://www.renren.com/ajaxLogin/login?1=1&uniqueTimestamp=2016932127568'
		request = urllib2.Request(loginUrl, urllib.urlencode(data))
		try:
			response = self.opener.open(request)
			usr = response.geturl()
			print url
		