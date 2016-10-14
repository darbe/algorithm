# -*- coding: utf-8 -*- 
import urllib  
import urllib2
import cookielib  
import re  
import json
import rsa
import binascii 
import  base64 
import urlparse  
import random
import config
class SinaLogin :
    def __init__ (self,username,userpasswd): 
        self.cookie = cookielib.CookieJar()    
        cookie_support = urllib2.HTTPCookieProcessor(self.cookie)   
        self.opener = urllib2.build_opener(cookie_support, urllib2.HTTPHandler)  
        urllib2.install_opener(self.opener)
        self.userName = username
        self.userPasswd = userpasswd
        self.servertime = ''
        self.nonce = ''
        self.pubkey = ''
        self.rsakv = ''
        self.showpin = 0
        self.pcid = ''
        self.success = False
        if not self.getServerData(config.PRELOGINURL):
            print 'prelogin error'
            exit(config.ERRORCODE)

    def getServerData(self,preLoginUrl):  
        content = urllib2.urlopen(config.PRELOGINURL).read()  
        elementPattern = re.compile(r'({[^{]+?})')
        try:  
            data = elementPattern.search(content)
            if not data :
                print 'sevice NULL'
                return False
            infor  = data.group(1)
            jsonData = json.loads(infor)

            self.servertime = str(jsonData['servertime'])  
            self.nonce = jsonData['nonce']  
            self.pubkey = jsonData['pubkey']  
            self.rsakv = jsonData['rsakv']
            self.showpin = int(jsonData['showpin'])
            self.pcid = jsonData['pcid']
            print jsonData
            return True 
        except:  
            print 'Get severtime error!'  
            return False
     
    def getPassword(self, password): 
        rsaPublickey = int(self.pubkey, 16)  
        key = rsa.PublicKey(rsaPublickey, 65537)
        message = str(self.servertime) + '\t' + str(self.nonce) + '\n' + str(password)  
        passwd = rsa.encrypt(message, key) 
        passwd = binascii.b2a_hex(passwd) 
        return passwd  

    def getUsername(self, username):  
        username_ = urllib.quote(username) 
        username = base64.encodestring(username_)[:-1] 
        return username 

    def getFormData(self):  
        userName = self.getUsername(self.userName)  
        password = self.getPassword(self.userPasswd)  
        postData = {  
            'entry':'weibo',  
            'gateway':'1',  
            'from':'',  
            'savestate':'7',  
            'useticket':'1',  
            'pagerefer':'http://weibo.com/p/1005052679342531/home?from=page_100505&mod=TAB&pids=plc_main',  
            #'pagerefer':'http://login.sina.com.cn/sso/logout.php?entry=miniblog&r=http%3A%2F%2Fweibo.com%2Flogout.php%3Fbackurl%3D%252F',  
            'vsnf':'1',  
            'su':userName,  
            'service':'miniblog',  
            'servertime':self.servertime,  
            'nonce':self.nonce,  
            'pwencode':'rsa2',  
            'rsakv':self.rsakv,  
            'sp':password,  
            'sr':'1920*1080',  
            'encoding':'UTF-8',
            'cdult':'2',
            'domain':'weibo.com',
            'prelt':'34', 
            'prelt':'115',  
            'url':'http://weibo.com/ajaxlogin.php?framelogin=1&callback=parent.sinaSSOController.feedBackUrlCallBack',  
            'returntype':'META'  
            }  
        #formData = urllib.urlencode(postData)  
        return  postData 
    def verifyCode(self):
        randint =  int(random.random()* 1e8)
        url = 'http://login.sina.com.cn/cgi/pin.php?r='+str(randint)+'&s=0&p='+self.pcid
        filename = 'pin.png' 
        print url  
        urllib.urlretrieve(url, filename)  
        code = raw_input('请输入验证码:')  
        return code 
   
    def login(self, loginUrl):   
            postData = self.getFormData() 
            urlPattern = re.compile('location.replace\([\"\']([^\)]+)[\"\']\)')
            reUrlPattern = re.compile(r'feedBackUrlCallBack\(([^\)]+)\)')

            headers = {'User-Agent':'Mozilla/5.0 (Windows NT 6.3; WOW64; rv:41.0) Gecko/20100101 Firefox/41.0'}  
            while not self.success:
                print postData
                formData = urllib.urlencode(postData) 
                request  = urllib2.Request(  
                        url = loginUrl,  
                        data = formData,  
                        headers = headers  
                )  
                response = self.opener.open(request)  
                content = response.read()
                print content.decode('GB2312')
                try:
                    dirtyUrl = urlPattern.search(content)
                    url = dirtyUrl.group(1)
                    print url
                    query = urlparse.parse_qs(urlparse.urlparse(url).query)
                    print query
                    print 'jellp'
                    retcode = query['retcode'][0] 
                    print retcode
                    if retcode != '0':
                        #print query['reason'][0].decode('gbk')
                        print config.FAILCODE[retcode]
                        if self.showpin and retcode == config.DISPLAY:
                            postData[self.pcid] = self.verifyCode()
                            continue
                        elif recode == config.TOOMANY:
                            return False
                    loginUrl = dirtyUrl.group(1) 
                    html = self.opener.open(loginUrl).read()
                    content = reUrlPattern.search(html) 
                    if not content :
                        print 'reurl info error login error'
                        return False
                    feedBack = content.group(1)
                    feedBack.replace('true', 'True').replace('null', 'None')
                    jsonData = json.loads(feedBack)
                    if not jsonData :
                        print 'error json loin error'
                        return False

                    print jsonData
                    self.success = jsonData['result']
                    userDomain = jsonData['userinfo']['userdomain'] 
                    if self.success:
                        print "Login success!"
                        break
                    else :
                        print 'unkonwn error' 
                        continue 
                except:  
                    print 'Login error!'  
                    return False  
  
            mainUrl = 'http://weibo.com' + '/u/' + jsonData['userinfo']['uniqueid'] + '/home' + userDomain 
            print mainUrl
            request = urllib2.Request(mainUrl)  
            response = self.opener.open(request)  
            text = response.read() 
            ofile = open("weibo.html","w+")  
            ofile.write(text)  
            ofile.close()  

sina = SinaLogin(config.USRNAME,config.PASSWD);
sina.login(config.LOGINURL)
