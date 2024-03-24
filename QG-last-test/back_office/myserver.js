//引入原生http模块
const http = require("http");
const url = require("url");
//引入mysql模块
const mysql = require("mysql");
//引入查询字符串模块
const querystring = require("querystring");
// 导入websocket的内置API
const WebSocket = require("ws");

// 创建 MySQL 数据库连接池
const pool = mysql.createPool({
    host: "localhost",
    user: "root",
    password: "password",
    database: "my_books",
});

// 处理来自客户端的请求-操作db数据库存到服务器数据库中
function handleRequest(request, response) {
    if (request.method === "GET" && request.url === "/books") {
        // 获取所有书籍
        pool.query("SELECT * FROM books", (error, results) => {
            if (error) throw error;
            response.setHeader("Content-Type", "application/json");
            response.end(JSON.stringify(results));
        });
    } else if (request.method === "POST" && request.url === "/books") {
        // 添加书籍
        let requestBody = "";
        request.on("data", (chunk) => {
            requestBody += chunk;
        });
        request.on("end", () => {
            let newBook = querystring.parse(requestBody);
            pool.query(
                `INSERT INTO books(title, author, description)
                    VALUES('${newBook.title}', '${newBook.author}', '${newBook.description}')`,
                (error, result) => {
                    if (error) throw error;
                    newBook.id = result.insertId;
                    response.setHeader("Content-Type", "application/json");
                    response.end(JSON.stringify(newBook));
                }
            );
        });
    } else if (request.method === "PUT" && /^\/books\/\d+$/.test(request.url)) {
        // 更新修改书籍
        let id = request.url.split("/").pop();
        let requestBody = "";
        request.on("data", (chunk) => {
            requestBody += chunk;
        });
        request.on("end", () => {
            let updatedBook = querystring.parse(requestBody);
            pool.query(
                `UPDATE books SET title='${updatedBook.title}', author='${updatedBook.author}', description='${updatedBook.description}'
                    WHERE id=${id}`,
                (error) => {
                    if (error) throw error;
                    updatedBook.id = id;
                    response.setHeader("Content-Type", "application/json");
                    response.end(JSON.stringify(updatedBook));
                }
            );
        });
    } else if (
        request.method === "DELETE" &&
        /^\/books\/\d+$/.test(request.url)
    ) {
        // 删除书籍
        let id = request.url.split("/").pop();
        pool.query(`DELETE FROM books WHERE id=${id}`, (error) => {
            if (error) throw error;
            response.end("Book deleted successfully.");
        });
    } else {
        // 处理其它请求
        response.statusCode = 404;
        response.end("Not found.");
    }
}

//创建 HTTP 服务器并监听请求
const server = http.createServer(handleBooksRequest);

//模拟服务器数据库
//已经审核过的书籍
const books = [
    {
        id: 1,
        title: "JavaScript高级程序设计",
        author: "Nicholas C. Zakas",
        publish_time: "2012-08-01",
    },
    {
        id: 2,
        title: "CSS揭秘",
        author: "Lea Verou",
        publish_time: "2015-06-15",
    },
    {
        id: 3,
        title: "Node.js实战",
        author: "Srephen Duguid & Jonathan Stillman",
        publish_time: "2014-12-01",
    },
];

//待审核的书籍
const tocheck_books = [
    {
        id: 1,
        title: "JavaScript高级程序设计",
        author: "Nicholas C. Zakas",
        publish_time: "2012-08-01",
    },
    {
        id: 2,
        title: "CSS揭秘",
        author: "Lea Verou",
        publish_time: "2015-06-15",
    },
    {
        id: 3,
        title: "Node.js实战",
        author: "Srephen Duguid & Jonathan Stillman",
        publish_time: "2014-12-01",
    },
];

//账号密码
const user_information = [
    //唯一管理员权限
    { id: 1, user_name: QGSTUDIO, password: 666666, flag: 1 },
    //普通用户权限
    { id: 2, user_name: Jiangzr, password: 0o40707, flag: 0 },
];

//定义路由处理函数
function handleBooksRequest(req, res) {
    const requestUrl = url.parse(req.url, true);
    if (requestUrl.pathname === "/book" && req.method === "GET") {
        // 获取所有书籍列表
        const responseBody = JSON.stringify(books);
        res.writeHead(200, { "Content-Type": "application/json" });
        res.end(responseBody);
    } else if (
        requestUrl.pathname.startsWith("/book/") &&
        req.method === "PATCH"
    ) {
        // 修改指定书籍状态
        const bookId = parseInt(requestUrl.pathname.substring(6));
        const status = req.body.status;
        const bookIndex = books.findIndex((book) => book.id === bookId);

        if (bookIndex !== -1) {
            books[bookIndex].status = status;
            const responseBody = JSON.stringify(books[bookIndex]);
            res.writeHead(200, { "Content-Type": "application/json" });
            res.end(responseBody);
        } else {
            const errorMessage = `No book with ID ${bookId} found!`;
            res.writeHead(404, { "Content-Type": "text/plain" });
            res.end(errorMessage);
        }
    } else {
        const errorMessage = `${req.method} method is not supported for ${requestUrl.pathname} endpoint!`;
        res.writeHead(404, { "Content-Type": "text/plain" });
        res.end(errorMessage);
    }
}

// 创建 WebSocket 服务器并绑定到 HTTP 服务器
const wss = new WebSocket.Server({ server });

wss.on("connection", function connection(ws) {
    console.log("WebSocket client connected");

    // 检索所有图书，并发送初始化消息
    db.query("SELECT * FROM books", function (err, results) {
        if (err) throw err;
        ws.send(JSON.stringify(results));
    });

    // 监听客户端发送的的更新请求
    ws.on("message", function incoming(message) {
        const book = JSON.parse(message);
        const query = "UPDATE books SET ? WHERE id = ?";
        db.query(query, [book, book.id], function (err) {
            if (err) throw err;
        });
    });

    // 设置心跳功能以保持连接
    const interval = setInterval(function ping() {
        ws.ping();
    }, 30000);

    ws.on("pong", function heartbeat() {
        clearInterval(interval);
        interval = setInterval(function ping() {
            ws.ping();
        }, 30000);
    });
});

// 启动服务器
server.listen(8888, function () {
    console.log("HTTP/WS server listening on port 3000");
});
