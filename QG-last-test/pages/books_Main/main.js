window.addEventListener('load',function() {
    // 页面加载动画
    var loading = document.getElementById('loading');
    var mask = document.getElementById('mask');
    setTimeout(function() {
        loading.style.display = 'none';
        mask.style.display = 'none';
    }, 2000);

    function goToPage(url) {
    loading.style.display='block'; // 显示加载动画
    mask.style.display='block'//显示遮罩层
    setTimeout(function() {
        location.href=url; // 跳转到指定页面
    }, 2000);
  }
})
    // Tab栏切换
    var limodules = document.querySelector('.li-module');
    var lis = limodules.querySelectorAll('li');
    var items = document.querySelectorAll('.item');

    lis[0].classList.add('current-module');

    for (let i = 0; i < lis.length; i++) {
    // 添加自定义属性
      lis[i].index = i;
      
    // 绑定点击事件
      lis[i].onclick = function () {

        for (let i = 0; i < lis.length; i++) {
              lis[i].classList.remove('current-module');
              items[i].style.display = 'none';
          }

          this.classList.add('current-module');
          var index = this.index;
          items[index].style.display = 'block';
          }
    }

    // 搜索框
    // 获取搜索关键字
function getKeywords(str) {
  // 可以根据实际需求修改搜索规则
  return str.trim().toLowerCase();
}

// 搜索匹配结果
function search(keyword) {
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/search?keyword=' + encodeURIComponent(keyword), true);
  xhr.send(null);
  xhr.onreadystatechange = function() {
    if (xhr.readyState === 4 && xhr.status === 200) {
      var data = JSON.parse(xhr.responseText);
      renderResult(data);
    }
  };
}

  // 渲染搜索结果
  function renderResult(data) {
    var container = document.getElementById('result-container');
    container.innerHTML = '';

    for (var i = 0; i < data.length; i++) {
      var item = document.createElement('div');
      item.innerHTML = data[i];
      container.appendChild(item);
    }
  }

  // 获取热门搜索
  function getHotKeywords() {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', '/hot_keywords', true);
    xhr.send(null);
    xhr.onreadystatechange = function() {
      if (xhr.readyState === 4 && xhr.status === 200) {
        var data = JSON.parse(xhr.responseText);
        renderHotKeywords(data);
      }
    };
  }

  // 渲染热门搜索
  function renderHotKeywords(data) {
    var container = document.getElementById('hot-keywords');
    container.innerHTML = '';

    for (var i = 0; i < data.length; i++) {
      var item = document.createElement('div');
      item.innerHTML = data[i];
      container.appendChild(item);
    }
  }

  // 绑定事件监听
  window.onload = function() {
    var input = document.getElementById('search-input');
    var hotKeywords = document.getElementById('hot-keywords');

    // 输入框获得焦点时显示热词提示
    input.addEventListener('focus', function() {
      hotKeywords.style.display = 'block';
    });

    // 输入框失去焦点时隐藏热词提示
    input.addEventListener('blur', function() {
      hotKeywords.style.display = 'none';
    });

    // 编写防抖函数，避免多次请求
    function debounce(fn, delay) {
      var timer = null;
      return function() {
        var context = this;
        var args = arguments;
        clearTimeout(timer);
        timer = setTimeout(function() {
          fn.apply(context, args);
        }, delay);
      };
    }

    // 输入内容时发起模糊搜索请求
    input.addEventListener(
      'input',
      debounce(function(e) {
        var keyword = getKeywords(e.target.value);
        search(keyword);
      }, 500)
    );

    // 获取并渲染热门搜索关键字
    getHotKeywords();
  };


    // //管理绑定点击事件
    // lis[4].onclick = function(){
    //   if(/*判断账户是否为管理员 */){
    //     //把display属性改为block；
    //   }else{
    //     alert("用户权限不足，功能无法使用");
    //   }
    // }


// 轮播图
    // 获取左右按钮和图片列表
    let oLeft = document.querySelector(".left");
    let oRight = document.querySelector(".right");
    let oImgList = document.querySelector(".img-list");
    // 克隆第一张图片
    let cloneFirstImg = oImgList.firstElementChild.cloneNode();
    // 克隆第一张图片
    let cloneLastImg = oImgList.lastElementChild.cloneNode();
    // 将第一张图片添加至图片列表的末尾
    oImgList.appendChild(cloneFirstImg);
    // 将最后一张图片添加至图片列表的首部
    oImgList.insertBefore(cloneLastImg,oImgList.querySelector("img"));
    // 图片索引 代表当前是第几张图片  index:1代表第一张图片  
    let index = 1;
    // 设置函数节流锁
    let lock = true;
    // 设置右按钮的功能
    function handleRightBtn() {
      if (!lock) return;
      index++;
      oImgList.style.transform = "translateX("+ index * -1226 + "px)";
      oImgList.style.transition = "0.5s ease";
      if (index === 6) {// 切换完之后再跳转
        index = 1; // 轮播完最后一张图后重置index的值
        setTimeout(() => {
          oImgList.style.transform = "translateX(" + index * -1226 + "px)";
          // 取消过渡 500毫秒之后切换最后一张
          oImgList.style.transition = "none";
        }, 500);     
      }
      // 设置小圆点的高亮
      setCircles();
      // 关锁
      lock = false;
      setTimeout(() => {
        lock = true;
      }, 500);
    }
    // 设置左按钮的功能
    function handleLeftBtn() {
      if (!lock) return;
        index--;
      if (index === 0) {// 切换完之后再跳转
        oImgList.style.transition = "none";
        oImgList.style.transform = "translateX(" + index * -1226 + "px)";
        //无过渡切换到最后一张
        index = 5;
        // 恢复过渡
        oImgList.style.transition = "0.5s ease";
        setTimeout(() => {
          oImgList.style.transform = "translateX(" + index * -1226 + "px)";
          // 取消过渡 500毫秒之后切换最后一张
          oImgList.style.transition = "none";
        }, 500);     
        } else {
        oImgList.style.transition = "0.5s ease";
        oImgList.style.transform = "translateX(" + index * -1226 + "px)";
      }
      // 设置小圆点的高亮
      setCircles();
      lock = false;
      setTimeout(() => {
        lock = true;
      }, 500);
    }
    // 右按钮的实现
    oRight.addEventListener("click", handleRightBtn);
    // 左按钮的实现  瞬间切换到假图然后拉到真实最后一张图片
    oLeft.addEventListener("click", handleLeftBtn);
    // 获取五个小圆点
    const circles = document.querySelectorAll(".circle");
    // 小圆点高亮的显示
    function setCircles() {
      for (let i = 0; i < circles.length; i++) {
        if (i+1 === index) {
          circles[i].classList.add("active");
        } else {
          circles[i].classList.remove("active");
        }
      }
    }
    // 小圆点点击切换图片 使用事件代理
    const oCircle = document.querySelector(".circle-list");
    oCircle.addEventListener("click", (e) => {
      // 当点击小圆点的时候
      if (e.target.nodeName.toLowerCase() === "li") {
        // 当前元素的data-n和index 一一对应
        const n = Number(e.target.getAttribute("data-n"));
        index = n;
        setCircles();
        oImgList.style.transition = "0.5s ease";
        oImgList.style.transform = "translateX("+ index * -1226 + "px)";
      }
    });
    // 自动轮播
    let autoplay = setInterval(handleRightBtn, 3000);
    const oWrap = document.getElementById("wrap");
    // 移入停止轮播
    oWrap.addEventListener("mouseenter", () => {
      clearInterval(autoplay);
    });
    // 移出继续轮播
    oWrap.addEventListener("mouseleave", () => {
      // 设表先关
      clearInterval(autoplay);
      autoplay = setInterval(handleRightBtn, 2000);


// 我的模块逻辑
      // 功能模块内容切换
      // Tab栏切换
      // 获取左侧栏目中的所有条目元素
      var sidebarItems = document.querySelectorAll('.me_shift input');
      // 为每个条目添加“click”事件监听器
      sidebarItems.forEach(function(item) {
        item.addEventListener('click', function() {
        // 获取该条目对应的自定义属性值
        var id = item.getAttribute('data-id');

        // 获取与该属性值匹配的下侧内容元素
        var contentItem = document.querySelector('#me-content .item-me[data-id="' + id + '"]');

        // 隐藏其他内容元素，并显示当前匹配的元素
        document.querySelectorAll('#me-content .item-me').forEach(function(item) {
          item.style.display = 'none';
        });

        contentItem.style.display = 'block';
      });
    });

          // 密码修改模块
    function updatePassword(event) {
      event.preventDefault(); // 阻止表单默认提交事件
    
      const oldPassword = document.getElementById('old-password').value;
      const newPassword = document.getElementById('new-password').value;
      const confirmNewPassword = document.getElementById('confirm-new-password').value;
    
      if (newPassword !== confirmNewPassword) {
        alert('两次输入的密码不匹配');
        return;
      }
    
      // 发送 POST 请求到后端
      fetch('/api/update-password', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ oldPassword, newPassword })
      })
      .then(response => response.json())
      .then(data => {
        if (data.success) {
          alert('密码修改成功，请重新登录');
          window.location.href = '/login'; // 重定向到登录页面
        } else {
          alert(data.message);
        }
      })
      .catch(error => console.error(error));
    }
      
          // 图书上传模块
          // 获取表单元素和相关输入框
          const uploadForm = document.querySelector('#upload-form');
          const nameInput = document.querySelector('#name');
          const phoneInput = document.querySelector('#phone');
          const titleInput = document.querySelector('#title');
          const descriptionInput = document.querySelector('#description');
          const categoryInput = document.querySelector('#category');
          const tagsInput = document.querySelector('#tags');
          const publisherInput = document.querySelector('#publisher');
          const publish_timeInput = document.querySelector('#publish-time');
          const coverInput = document.querySelector("#file-img-input-1");
          const contentInput = document.querySelector("#file-img-input-2")

          //图片预览效果
          const input_img = document.querySelector('input[accept="image/*"]');
          input_img.addEventListener('change', function() {
            var file = this.files[0];
            var reader = new FileReader();
            reader.addEventListener('load', function() {
              var base64 = reader.result;
              var img = document.createElement('img');
              img.src = base64;
              document.body.appendChild(img);
            });
            reader.readAsDataURL(file);
          });


            // 保存草稿
          function saveDraft() {
            const bookDetails = {
              name: nameInput.value,
              phone: phoneInput.value,
              title: titleInput.value,
              description: descriptionInput.value,
              // cover: coverInput.value,
              // content: contentInput.value,
              publisher: publisherInput.value,
              publish_time: publish_timeInput.value,
              category: categoryInput.value,
              tags: tagsInput.value,
            };
            //本地存储
            localStorage.setItem('bookDraft', JSON.stringify(bookDetails));
          }

          // 恢复草稿
          function restoreDraft() {
            const bookDetails = JSON.parse(localStorage.getItem('bookDraft'));
            if (bookDetails) {
              nameInput.value = bookDetails.name;
              phoneInput.value = bookDetails.phone;
              titleInput.value = bookDetails.title;
              descriptionInput.value = bookDetails.description;
              // coverInput.value = bookDetails.cover;
              // contentInput.value = bookDetails.content;
              publisherInput.value = bookDetails.publisher;
              publish_timeInput.value = bookDetails.publish_time;
              categoryInput.value = bookDetails.category;
              tagsInput.value = bookDetails.tags;
            }
          }

          // 页面加载时恢复草稿
          restoreDraft();

          // 绑定事件监听器来自动保存草稿
          setInterval(saveDraft, 1000);

          //封面与内容重置
          const botton_img_reset = document.querySelector(".button_img_reset");
          const botton_text_reset = document.querySelector(".button_text_reset");
          function clearImg(event){
            // cover.value = null
          }
          function clearText(event){
            // content.value = null
          }
          botton_img_reset.addEventListener('click',clearImg);
          botton_text_reset.addEventListener('click',clearText);

          // 监听表单提交事件
          uploadForm.addEventListener('submit', (event) => {
            
          // 阻止表单默认提交行为
            event.preventDefault();
          
            // 检查输入是否合法
            if (!isNameValid() || !isPhoneValid() || !isPublisherValid() || !isTitleValid() || !isDescriptionValid() || !isCoverValid() || !isContentValid() || !isCategoryValid()) return;

            //完成表单提交逻辑
            const formData = new FormData(uploadForm);
            // 发送 AJAX 请求
              const xhr = new XMLHttpRequest();
              xhr.open('POST', 'http://localhost:3000');//服务器端口号
              xhr.setRequestHeader('Content-Type', 'multipart/form-data');
              xhr.onreadystatechange = function() {
                if (xhr.readyState === 4 && xhr.status === 200) {
                  console.log('数据上传成功');
                } else if (xhr.readyState === 4) {
                  console.log('数据上传失败');
                }
              };
              xhr.send(formData);
          });

          // 监听封面文件输入框变化事件
          coverInput.addEventListener('change', () => {
            // 预览图片
            const file = coverInput.files[0];
            if (file) {
              const reader = new FileReader();
              reader.readAsDataURL(file);
              reader.onload = () => {
              coverPreview.src = reader.result;
              };
              botton_img_reset.disabled = false;
            }
          });

          // 表单验证函数
          function isNameValid() {
            if (nameInput.validity.valueMissing) {
              alert('请填写姓名');
              nameInput.focus();
              return false;
            }
            return true;
          }

          function isPhoneValid() {
            if (phoneInput.validity.valueMissing) {
              alert('请填写电话号码');
              phoneInput.focus();
              return false;
            } else if (phoneInput.validity.patternMismatch) {
              alert('电话号码格式错误，请重新填写');
              phoneInput.focus();
              return false;
            }
            return true;
          }

          function isPublisherValid() {
            if (publisherInput.validity.valueMissing) {
              alert('请填写出版社');
              publisherInput.focus();
              return false;
            }
            return true;
          }

          function isTitleValid() {
            if (titleInput.validity.valueMissing) {
              alert('请填写书名');
              titleInput.focus();
              return false;
            }
            return true;
          }

          function isDescriptionValid() {
            if (descriptionInput.validity.valueMissing) {
              alert('请填写书籍介绍');
              descriptionInput.focus();
              return false;
            }
            return true;
          }

          function isCoverValid() {
            if (coverInput.validity.valueMissing) {
              alert('请上传封面');
              coverInput.focus();
              return false;
            } else if (!/\.(jpe?g|png|gif)$/i.test(coverInput.files[0].name)) {
              alert('仅支持上传JPEG、PNG或GIF格式的图片');
              coverInput.focus();
              return false;
            }
            return true;
          }

          function isContentValid() {
            if (contentInput.validity.valueMissing) {
              alert('请上传书籍内容文件');
              contentInput.focus();
              return false;
            } else if (!/\.txt$/i.test(contentInput.files[0].name)) {
              alert('仅支持上传TXT格式的文件');
              contentInput.focus();
              return false;
            }
            return true;
          }

          function isCategoryValid() {
            if (categoryInput.validity.valueMissing) {
              alert('请选择书籍分类');
              categoryInput.focus();
              return false;
            }
            return true;
          }

    // 分类逻辑
    // Tab栏切换
// 获取左侧栏目中的所有条目元素
const kind_sidebarItems = document.querySelectorAll('.kind_sidebar li');
const kind_contentItems = document.querySelectorAll('.kind_content .kind_item');
kind_contentItems[0].style.display = 'block';
// 为每个条目添加“click”事件监听器
kind_sidebarItems.forEach(function(item) {
    item.addEventListener('click', function() {
    // 获取该条目对应的自定义属性值
    const kind_id = item.getAttribute('data-id');
    
    // 获取与该属性值匹配的右侧内容元素
    const kind_contentItem = document.querySelector('.kind_content .kind_item[data-id="' + kind_id + '"]');
    
    // 隐藏其他内容元素，并显示当前匹配的元素
    kind_contentItems.forEach(function(item) {
      item.style.display = 'none';
    });
    
    kind_contentItem.style.display = 'block';


    //这一步是为了防止，点击事件的过度发生。
    let myTimer = -1;
    //1、获取当前滚动了多少距离
    //2、启动定时器，以一定时间减少响应的滚动距离
    let scrollTo = document.documentElement.scrollTop || document.body.scrollTop
    if(myTimer == -1){
        myTimer = setInterval(() => {
            scrollTo -= 60
            if(scrollTo<=580){
                scrollTo = 580
                window.clearInterval(myTimer)
                myTimer = -1
            }
            
            window.scrollTo(0,scrollTo) //这是值  是指离开网页顶部的距离   
        }, 10)
      };
    })
  })

  
  
  
  
  
  
  
  
  
  
  
  
  
  

































})
