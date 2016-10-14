# -*- coding: utf-8 -*-
PRELOGINURL = 'https://login.sina.com.cn/sso/prelogin.php?entry=weibo&callback=sinaSSOController.preloginCallBack&su=emhhbmd3dXpoYW8lNDBzaW5hLmNu&rsakt=mod&checkpin=1&client=ssologin.js(v1.4.18)&_=1476364797049'
LOGINURL = 'http://login.sina.com.cn/sso/login.php?client=ssologin.js(v1.4.18)'
FAILCODE =  { 
                '-1': '登录成功',
                '0': '登录系统错误，请稍后尝试',
                '1': '您的用户名和密码不匹配',
                '2': '您的用户名和密码不匹配',
                '4': '您的用户名和密码不匹配',
                '8': '请输入帐号，密码',
                '16': '您的账号已停止使用',
                '32': '帐号未激活，请激活帐号',
                '6102': '请输入密码和账号',
                '101': '登录名或密码错误',
                '4049': '为了您的帐号安全，请输入验证码',
                '4038': '登录次数过多'
            }
DISPLAY = '4049'
TOOMANY = '4038'
ERRORCODE = -1
USRNAME = 'zhangwuzhao@sina.cn'
PASSWD = '530698376'