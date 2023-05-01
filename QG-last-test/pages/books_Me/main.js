window.addEventListener('load',function(){
  //加载动画模块
const loading = document.getElementById('loading');
const mask = document.getElementById('mask');
    setTimeout(function() {
        loading.style.display = 'none';
        mask.style.display = 'none';
    }, 2000);

    function goToPage(url) {
    var loading = document.getElementById('loading');
    var mask = document.getElementsById('mask');
    loading.style.display='block'; // 显示加载动画
    mask.style.display='block'//显示遮罩层
    setTimeout(function() {
        location.href=url; // 跳转到指定页面
    }, 2000);
    }


    
// Tab栏切换
// 获取左侧栏目中的所有条目元素
var sidebarItems = document.querySelectorAll('.sidebar li');

// 为每个条目添加“click”事件监听器
sidebarItems.forEach(function(item) {
  item.addEventListener('click', function() {
    // 获取该条目对应的自定义属性值
    var id = item.getAttribute('data-id');
    
    // 获取与该属性值匹配的右侧内容元素
    var contentItem = document.querySelector('.content .item[data-id="' + id + '"]');
    
    // 隐藏其他内容元素，并显示当前匹配的元素
    document.querySelectorAll('.content .item').forEach(function(item) {
      item.style.display = 'none';
    });
    
    contentItem.style.display = 'block';
  });
});






// 用户密码修改模块
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
    cover: coverInput.value,
    content: contentInput.value,
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
    coverInput.value = bookDetails.cover;
    contentInput.value = bookDetails.content;
    publisherInput.value = bookDetails.publisher;
    publish_timeInput.value = bookDetails.publish_time;
    categoryInput.value = bookDetails.category;
    tagsInput.value = bookDetails.tags;
  }
}

// 绑定事件监听器来自动保存草稿
setInterval(saveDraft, 1000);

// 页面加载时恢复草稿
restoreDraft();

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
    cancelCoverButton.disabled = false;
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






})