LOGINURL = r'http://www.renren.com/ajaxLogin/login?1=1&uniqueTimestamp=2016932127568'
ICONURL = r'http://icode.renren.com/getcode.do?t=web_login&rnd=Math.random()'

USRNAME = '1073889058@qq.com'
PASSWD = '530698376'

FAILCODE =  { 
                '-1': '登录成功',
                '0': '登录系统错误，请稍后尝试',
                '1': '您的用户名和密码不匹配',
                '2': '您的用户名和密码不匹配',
                '4': '您的用户名和密码不匹配',
                '8': '请输入帐号，密码',
                '16': '您的账号已停止使用',
                '32': '帐号未激活，请激活帐号',
                '64': '您的帐号需要解锁才能登录',
                '128': '您的用户名和密码不匹配',
                '512': '请您输入验证码',
                '4096': '登录系统错误，稍后尝试'
            }
