//数据存储模式
//1.图书类:对应一本图书
//{         //id:id.value,
            //name: nameInput.value,
            //phone: phoneInput.value,
            //title: titleInput.value,
            //description: descriptionInput.value,
            //cover: coverInput.value,
            //content: contentInput.value,
            //publisher: publisherInput.value,
            //publish_time: publish_timeInput.value,
            //category: categoryInput.value,
            //tags: tagsInput.value,
            //like: like.value,
            //collect: collect.value,
//}

//2.用户类:对应一个用户
//{         //id:id.value,
            //username: username.value,
            //password: password.value,
            //flag: flag.value,权限状态：管理员唯一标识符
//}

//3.评论类:对应一条评论
//{
            //comment_user: comment_user.value,
            //comment: comment.value,
            //comment_time: comment_time.value,
            //comment_book: comment_book.value,
            //comment_others: comment_others.value,
//}
/*---------------------------------数据模拟挂载--------------------------------------*/

//模拟服务器数据库
//已经审核过的书籍
const books = [];

//待审核的书籍
const tocheck_books = []

//账号密码
const userinfo = [
    //唯一管理员权限
    {id: 1, username: "zs", password: "123456", flag: 1},//管理员
    //普通用户权限
    {id: 2, username: "ls", password: "abcdef", flag: 0} 
]
/*----------------------------------模块创建引入-----------------------------------------*/

//引入原生http模块
const http = require('http');
const fs = require("fs");   //fs.readFile读取文件，fs.writeFile写入内容
const path = require("path");
var url = require('url');
//引入mysql模块
const mysql = require('mysql');
//引入查询字符串模块
const querystring = require('querystring');
// 导入websocket的内置API
const WebSocket = require('ws');
const { isUtf8 } = require('buffer');

// 创建 MySQL 数据库连接池
const pool = mysql.createPool({
    host: '127.0.0.1',
    port: 3306,
    user: 'root',
    password: '0707',
    database: 'qg-books',
});


// 创建HTTP服务器
const server = http.createServer((req, res) => {
  // 设置响应头
    res.setHeader('Content-Type', 'application/json; charset=utf-8');


/*------------------------------------路由处理函数-------------------------------------*/

  // 登陆注册处理请求
    if (req.method === 'POST' && req.url === '/register') {//请求路径为http://127.0.0.1:8888/register
            let postData = '';
            req.on('data', chunk => {
                postData += chunk.toString();
            });
            req.on('end', () => {
                const { username, password } = postData;
            
                pool.getConnection((err, connection) => {
                if (err) {
                    console.error(err);
                    res.statusCode = 500;
                    res.end(JSON.stringify({
                    code: 1,
                    msg: '注册失败'
                    }));
                    return;
                }
                //用户名查重
                const selectSql = `SELECT * FROM users WHERE username='${username}'`;
                connection.query(selectSql, (err, results) => {
                    if (err) {
                    console.error(err);
                    res.statusCode = 500;
                    res.end(JSON.stringify({
                        code: 1,
                        msg: '注册失败'
                    }));
                    return;
                    }
                
                    if (results.length > 0) {
                    res.statusCode = 200;
                    res.end(JSON.stringify({
                        code: 1,
                        msg: '用户名已存在',
                    }));
                    return;
                    }
                
                  // 添加新用户
                    const insertSql = `INSERT INTO users(username, password) VALUES('${username}', '${password}')`;
                    connection.query(insertSql, (err, results) => {
                    if (err) {
                        console.error(err);
                        res.statusCode = 500;
                        res.end(JSON.stringify({
                        code: 1,
                        msg: '注册失败'
                        }));
                        return;
                    }
                
                    res.statusCode = 200;
                    res.end(JSON.stringify({
                        code: 0,
                        msg: '注册成功',
                        
                    }));
                });
            
                  // 释放连接
                    connection.release();
                    });
                });
            });
    } else if (req.method === 'POST' && req.url === '/login') {//请求路径为http://127.0.0.1:8888/login
            let postData = "";
            req.on('data', chunk => {
                postData += chunk.toString();
            });
            req.on('end', () => {
                const { username, password } = postData;
            
                pool.getConnection((err, connection) => {
                if (err) {
                    console.error(err);
                    res.statusCode = 500;
                    res.end(JSON.stringify({
                    code: 1,
                    msg: '登录失败'
                    }));
                    return;
                }
            
                const selectSql = `SELECT *  FROM users WHERE username='${username}'`;
                connection.query(selectSql, (err, results) => {
                    if (err) {
                    console.error(err);
                    res.statusCode = 500;
                    res.end(JSON.stringify({
                        code: 1,
                        msg: '登录失败'
                    }));
                    return;
                    }
                
                    if (results.length === 0 || results[0].password !== password) {
                    res.statusCode = 200;
                    res.end(JSON.stringify({
                        code: 1,
                        msg: '用户名或密码错误'
                        
                    }));
                    return;
                    }
                
                    res.statusCode = 200;
                    res.end(JSON.stringify({
                    code: 0,
                    msg: '登录成功'
                    }));
                
                  // 释放连接
                    connection.release();
                    });
                });
            });
    } else if (req.method === 'GET' && req.url === 'books') {//请求路径为http://127.0.0.1:8888/books
        // 获取所有书籍
        pool.query('SELECT * FROM books', (error, results) => {
            if (error) throw error;
            response.setHeader('Content-Type', 'application/json');
            response.end(JSON.stringify(results));
        });
    } else if (req.method === 'POST' && pathname === '/addBook') {//请求路径为http://127.0.0.1:8888/addBook
    // 处理新增图书请求
        let postData = '';
        req.on('data', chunk => {
            postData += chunk.toString();
        });
        req.on('end', () => {
        const {  
                name,
                phone,
                title,
                description,
                cover,
                content,
                publisher,
                publish_time,
                category,
                tags,
                like,
                collect
            } = qs.parse(postData);

        pool.getConnection((err, connection) => {
        if (err) {
            console.error(err);
            res.statusCode = 500;
            res.end(JSON.stringify({
            code: 1,
            msg: '添加失败'
            }));
            return;
        }

        // 判断当前图书是否已存在
        const selectSql = `SELECT * FROM books WHERE title='${title}'`;
        connection.query(selectSql, (err, results) => {
            if (err) {
            console.error(err);
            res.statusCode = 500;
            res.end(JSON.stringify({
                code: 1,
                msg: '添加失败'
            }));
            return;
            }

            if (results.length > 0) {
            res.statusCode = 200;
            res.end(JSON.stringify({
                code: 1,
                msg: '当前图书已存在'
            }));
            return;
            }

          // 新增图书
            const addSql = `INSERT INTO books(name, phone, title, description, cover, content, publisher, publish_time, category, tags, like, collect) VALUES('${name}','${phone}', '${title}','${description}','${cover}','${content}', '${publisher}', '${publish_time}', '${category}',  '${tags}', '${like}','${collect}' )`;
            connection.query(addSql, (err, results) => {
            if (err) {
                console.error(err);
                res.statusCode = 500;
                res.end(JSON.stringify({
                code: 1,
                msg: '添加失败'
                }));
                return;
            }

            res.statusCode = 200;
            res.end(JSON.stringify({
                code: 0,
                msg: '添加成功'
            }));
            });

          // 释放连接
            connection.release();
        });
        });
    });
    

    } else if (req.method === 'POST' && pathname === '/updateBook') {
    // 处理更新图书请求
    let postData = '';
    req.on('data', chunk => {
        postData += chunk.toString();
    });
    req.on('end', () => {
        const { 
            id, 
            name,
            phone,
            title,
            description,
            cover,
            content,
            publisher,
            publish_time,
            category,
            tags,
            like,
            collect
        } = qs.parse(postData);

        pool.getConnection((err, connection) => {
        if (err) {
            console.error(err);
            res.statusCode = 500;
            res.end(JSON.stringify({
            code: 1,
            msg: '更新失败'
            }));
            return;
        }

        // 更新图书信息
        const updateSql = id ? `UPDATE books SET name='${name}', phone='${phone}', title='${title}', description= '${description}', cover='${cover}',content='${content}', publisher='${publisher}', publish_time='${publish_time}', category='${category}',  tags='${tags}', like='${like}', collect='${collect}' WHERE id=${id}` : `UPDATE books SET name='${name}', phone='${phone}', title='${title}', description= '${description}', cover='${cover}',content='${content}', publisher='${publisher}', publish_time='${publish_time}', category='${category}',  tags='${tags}', like='${like}', collect='${collect}' WHERE title='${title}'`;
        connection.query(updateSql, (err, results) => {
            if (err) {
            console.error(err);
            res.statusCode = 500;
            res.end(JSON.stringify({
                code: 1,
                msg: '删除失败'
            }));
            return;
            }

            res.statusCode = 200;
            res.end(JSON.stringify({
            code: 0,
            msg: '删除成功'
            }));
        });

        // 释放连接
        connection.release();
        });
    });

    } else if (req.method === 'DELETE' && pathname === '/deleteBook') {//请求路径为http://127.0.0.1:8888/deleteBook
        // 处理删除图书请求
        let postData = '';
        req.on('data', chunk => {
            postData += chunk.toString();
        });
        req.on('end', () => {
            const { id, title } = qs.parse(postData);

        pool.getConnection((err, connection) => {
        if (err) {
            console.error(err);
            res.statusCode = 500;
            res.end(JSON.stringify({
            code: 1,
            msg: '删除失败'
            }));
            return;
        }

        // 删除图书
        const deleteSql = id ? `DELETE FROM books WHERE id=${id}` : `DELETE FROM books WHERE title='${title}'`;
        connection.query(deleteSql, (err, results) => {
            if (err) {
            console.error(err);
            res.statusCode = 500;
            res.end(JSON.stringify({
                code: 1,
                msg: '删除失败'
            }));
            return;
            }

            res.statusCode = 200;
            res.end(JSON.stringify({
            code: 0,
            msg: '删除成功'
            }));
        });

        // 释放连接
        connection.release();
        });
        });
    } else {
            res.statusCode = 404;
            res.end(JSON.stringify({
                code: 1,
                msg: '接口不存在'
            }));
    }



});//所有路由处理函数结束


/*---------------------------------------同步ws----------------------------------------*/
// 创建 WebSocket 服务器并绑定到 HTTP 服务器
const ws = new WebSocket.Server({ server });

ws.on('connection', function connection(ws) {
    console.log('WebSocket client connected');

/*// 定义---书籍列表页面---的同步处理函数
//   // 检索所有图书，并发送初始化消息
//   db.query('SELECT * FROM books', function (err, results) {
//     if (err) throw err;
//     ws.send(JSON.stringify(results));
//     });

//   // 监听客户端发送的的更新请求
//     ws.on('message', function incoming(message) {
//     const book = JSON.parse(message);
//     const query = 'UPDATE books SET ? WHERE id = ?';
//     db.query(query, [book, book.id], function (err) {
//         if (err) throw err;
//     });
//     });*/

  // 设置心跳功能以保持连接
    const interval = setInterval(function ping() {
    ws.ping();
    }, 30000);

    ws.on('pong', function heartbeat() {
    clearInterval(interval);
    interval = setInterval(function ping() {
        ws.ping();
    }, 30000);
    });
});

// 启动服务器
server.listen(8888, function () {
    console.log('HTTP/WS server listening on port 8888');
});












