	//本地存储功能
	function saveDate(idx,data){
		localStorage.setItem("todolist"+idx,JSON.stringify(data))
}
	
	var input = document.querySelector('.form input'); //获取事件输入框
  var addBtn = document.querySelector('#add'); //获取添加按钮
  var list = document.querySelector('.list'); //获取事件列表ul

  //点击添加按钮
  addBtn.addEventListener('click', function () { //使用监听器addEventListener
    //使用DOM添加insertAdjacentHTML，第一个参数:添加的位置；第二个参数:添加的内容
    //每次添加的li均添加到ul内的第一个li之前（afterbegin）
    list.insertAdjacentHTML('afterbegin', `
    <li class="item">
          <!-- 事件区域 -->
          <span class="info">${input.value}</span>
          <!-- 按钮区域 -->
          <div class="btn">
            <button class="edit">编辑</button>
            <button class="fin">完成</button>
            <button class="del">删除</button>
          </div>
        </li>
    `);

    //由于之前设置点击添加按钮后新元素item会被添加到插入元素内部的第一个子节点之前
    //所以我们应该对list的第一个子元素节点进行操作，否则新增事件无法被删除、修改和完成
    //删除
    list.firstElementChild.querySelector('.del').addEventListener('click', function () {
      var item = this.parentNode.parentNode
      item.remove()
    })
    //完成
    list.firstElementChild.querySelector('.fin').addEventListener('click', function () {
      var item = this.parentNode.parentNode
      item.classList.add('finished')
    })
    //修改
    list.firstElementChild.querySelector('.edit').addEventListener('click', function () {
      var item = this.parentNode.parentNode
      item.querySelector('.info').innerText = prompt('请修改你的事件：')
			saveDate(first,item.querySelector('.info').innerText)
    })

		
  })

	


 
  var delBtns = document.querySelectorAll('.del'); //获取删除按钮
  var finBtns = document.querySelectorAll('.fin'); //获取完成按钮
  var editBtns = document.querySelectorAll('.edit'); //获取编辑按钮
 
  //遍历，有几个删除按钮则相当于有几个事件（li）
  for (var idx = 0; idx < delBtns.length; idx++) {
    //点击删除按钮
    delBtns[idx].addEventListener('click', function () {
      var item = this.parentNode.parentNode //删除按钮父级的父级，即类名为item的li(该按钮所在的行)，一个li即一个事件行
      item.remove(); //点击删除按钮后删除该条li
    })
 
    //点击完成按钮
    finBtns[idx].addEventListener('click', function () {
      var item = this.parentNode.parentNode; //获取该条事件行
      //classList属性可以返回一个元素类属性集合
      item.classList.add('finished'); //点击完成按钮后为该行添加新类名finished，以实现新样式
    })
 
    //点击编辑按钮
    editBtns[idx].addEventListener('click', function () {
      var item = this.parentNode.parentNode; //获取该条事件行
      item.querySelector('.info').innerText = prompt('请修改你的事件：'); //点击编辑后将内容插入类名为info的span并弹出系统提示框	
			saveDate(idx,item.querySelector('.info').innerText)
		})
	}
  
