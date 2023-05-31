// 图书信息 
// 获取DOM元素


// 提交评论表单
// commentForm.addEventListener("submit", function(event) {
//   event.preventDefault(); // 阻止表单默认提交行为
//   var commentInput = document.getElementById("comment");
//   var commentText = commentInput.value;
//   var newComment = createCommentElement(commentText);
//   commentsList.appendChild(newComment);
//   commentInput.value = ""; // 清空评论输入框
// });

// 创建新评论元素
document.getElementById("btn").onclick=function(){send()};
function send(){
    var g=new Date();
    var value= document.getElementById("typing").value;
    var p= document.createElement("p");
    p.innerHTML="用户："+value+'<hr>'+g.toUTCString();
    document.getElementById("commend").prepend(p);
  }

/* 管理员的删除权限 */


/* 收藏书架 */


/* 评论区
commentForm.addEventListener("submit", function(event) {
  event.preventDefault(); // 阻止表单默认提交行为
  var commentInput = document.getElementById("comment");
  var commentText = commentInput.value;
  var xhr = new XMLHttpRequest();
  xhr.open("POST", "/api/comments", true);
  xhr.setRequestHeader("Content-type", "application/json");
  xhr.onreadystatechange = function() {
    if (xhr.readyState === 4 && xhr.status === 200) {
      var newComment = createCommentElement(commentText);
      commentsList.appendChild(newComment);
      commentInput.value = ""; // 清空评论输入框
    }
  };
  var data = {
    book: "JavaScript高级程序设计",
    comment: commentText
  };
  xhr.send(JSON.stringify(data));
});*/






