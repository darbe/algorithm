import urllib
import  urllib2
import cookielib
import re
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
            'email' : self.username,
            'password' : self.passwd
        }
        loginUrl = 'http://www.renren.com/ajaxLogin/login?1=1&uniqueTimestamp=2016932127568'
        request = urllib2.Request(loginUrl, urllib.urlencode(data).encode(encoding='UTF8'))
        try:
            #response = self.opener.open(request)
            #url = response.geturl()
            #print(url)
            url = urllib2.urlopen('http://www.renren.com').geturl()
            print(url)
            if re.match('http://www.renren.com/[\d]{9}',url):
                print('success')
                return True
            else:
                print('not corret')
                return False
        except Exception as e:
            print(e)
            return False

usrname = '1073889058@qq.com'
password = '9e86d9a1d286f43db1d4a3076d13f0502645d8db48c999296ebbf46a5ade7bb8'
helper = LoginHelper(usrname,password,'')
helper.login()
