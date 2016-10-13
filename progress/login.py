import urllib
import urllib.request as urlib2
import http.cookiejar as jar
import re
class LoginHelper:
    def __init__ (self,username,passwd,path):
        self.username = username
        self.passwd = passwd
        self.path = path
        self.cookie = jar.LWPCookieJar()
        self.opener = urlib2.build_opener(urlib2.HTTPCookieProcessor(self.cookie))
        urlib2.install_opener(self.opener)
    def geticode(self,icodeUrl) :
        image = self.getResponse(icodeUrl).read()
        print(type(image))
        self.writeFile('icode.jpg',image)
    def writeFile(self,filename,data):
        try:
            ofile = open(filename,'wb')
            ofile.write(data)
            ofile.close()
        except IOError:
            print('IOError')
    def getResponse(self, url, data = None):
        if data is not None:
            request = urlib2.Request(url, urllib.parse.urlencode(data).encode(encoding='UTF8'))
        else:
            request = urlib2.Request(url)
        try :

            response = self.opener.open(request)
        except Exception as e:
            print(e)
            return None
        return response
    def login(self,loginUrl = None,icodeUrl = None):
        data = {
            'email' : self.username,
            'password' : self.passwd,
        }
        icodeUrl = 'http://icode.renren.com/getcode.do?t=web_login&rnd=Math.random()'
        self.geticode(icodeUrl);
        icode = input("input icode");
        data['icode'] = icode
        print(data)
        try:
            response = self.getResponse(loginUrl,data)
            url = response.geturl()
            content = response.read().decode('utf-8')
            print(content)
            print(url)
            for item in self.cookie:
                print (item.name, item.value)
            url = urlib2.urlopen('http://www.renren.com').geturl()
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

#password = '9e86d9a1d286f43db1d4a3076d13f0502645d8db48c999296ebbf46a5ade7bb8'
password = '530698376'
helper = LoginHelper(usrname,password,'')
loginUrl = 'http://www.renren.com/ajaxLogin/login?1=1&uniqueTimestamp=2016932127568'
helper.login(loginUrl)
