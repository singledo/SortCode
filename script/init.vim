filetype off                  " required

function PRINT()
    call append(line("."), "printf(\"[%s] [%s],[%d]\\n\",TAG, __FUNCTION__,__LINE__);")
endfunction

set nu
set guioptions-=r
set guioptions-=L
set guioptions-=b
set showtabline=0
set guifont=Monaco:h13
set background=dark     "设置背景色"
set nowrap  "设置不折行"
set fileformat=unix "设置以unix的格式保存文件"
set showmatch   "显示匹配的括号"
set scrolloff=5     "距离顶部和底部5行"
set laststatus=2    "命令行为两行"
set fenc=utf-8      "文件编码"
set backspace=2
set matchtime=5
set hlsearch        "高亮搜索项"
set whichwrap+=<,>,h,l
set autoread
set directory=~/vimswap
set tags=tags
syntax on
set cindent
set autoindent
set cinoptions=:0,l1,t0,g0,+10,(0,+s    " Linux Kernel CodingStyle
set completeopt=longest,menuone
set ts=4

" vim　主题
colorscheme 1989
set foldmethod=indent
set foldlevel=99

" cscope 跳转
if has("cscope")
	set csprg=/usr/bin/cscope
	set csto=0
	"find cscope db prior
	set cst
	" use cstags
	set nocsverb
	" add any database in current directory
	if filereadable("cscope.out")
		cs add cscope.out
		" else add database pointed to by environment
	elseif $CSCOPE_DB != ""
		cs add $CSCOPE_DB
	endif
	set csverb
endif



" set list
set completeopt=menu,menuone

" 搜索时高亮多个匹配
set incsearch
" 取消高亮
nnoremap <F4> : nohl <CR>
" vim 复制到系统剪切板
nnoremap <F2> : set clipboard=unnamed <CR>
" 取消复制到系统剪切板
nnoremap <F3> : set clipboard^=unnamed,unnamedplus <CR>
nmap <F5> : call PRINT() <cr>

" 窗口跳转
map <c-l> <c-w>l
map <c-k> <c-w>k
map <c-j> <c-w>j
map <c-h> <c-w>h

let mapleader=","

" 设置高亮行和列
set cursorcolumn
set cursorline

let g:indent_guides_enable_on_vim_startup=1
" 从第二层开始可视化显示缩进
let g:indent_guides_start_level=1
" 色块宽度
let g:indent_guides_guide_size=1
" 快捷键 i 开/关缩进可视化
nmap <Leader>t <Plug>IndentGuidesToggle

" Plugin 'airblade/vim-gitgutter'
" 基于git 标记新增，删除，和修改
set updatetime=100
let g:gitgutter_sign_added = '++'
let g:gitgutter_sign_modified = 'xx'
let g:gitgutter_sign_removed = '--'
let g:gitgutter_max_signs=1500
highlight GitGutterAdd    guifg=#009900 ctermfg=2
highlight GitGutterChange guifg=#bbbb00 ctermfg=3
highlight GitGutterDelete guifg=#ff2222 ctermfg=1

" Plugin 'luochen1990/rainbow'
" 给配对的 {} () 配色
let g:rainbow_active = 1

" Plugin 'scrooloose/nerdtree'
"文件浏览
let NERDTreeIgnore=['\.pyc','\~$','\.swp','\.out','tags']
let NERDTreeShowBookmarks=1
" file explore
map <C-n> :NERDTreeToggle<CR>
let g:NERDTree_title='FILE'

"Plugin 'majutsushi/tagbar'
" 函数列表
nmap <C-f> :TagbarToggle<CR>
let g:tagbar_autofocus = 1

" Plugin 'kien/ctrlp.vim'
" 文件快速搜索
let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlP'
let g:ctrlp_custom_ignore = '\v[\/]\.(git|hg|svn|pyc)$'
let g:ctrlp_max_height = 15

" Plugin 'BurntSushi/ripgrep.git'
" vim 中集成搜索工具
nnoremap <Leader>r :CtrlSF  
let g:ctrlsf_search_mode = 'sync'

 
" Plugin 'MarcWeber/vim-addon-mw-utils'
" Plugin 'tomtom/tlib_vim'
" Plugin 'SirVer/ultisnips'
" 代码补全
let g:UltiSnipsSnippetDirectories=["~/.vim/Snippets"]
let g:UltiSnipsExpandTrigger="<c-e>"
let g:UltiSnipsJumpForwardTrigger="<c-j>"
let g:UltiSnipsJumpBackwardTrigger="<c-k>"

" Plugin 'godlygeek/tabular'
" Plugin 'plasticboy/vim-markdown'
" Plugin 'mzlogin/vim-markdown-toc'
" markdown 插件
nmap <silent> <F6> <Plug>MarkdownPreview
imap <silent> <F6> <Plug>MarkdownPreview
nmap <silent> <F7> <Plug>StopMarkdownPreview
imap <silent> <F7> <Plug>StopMarkdownPreview
" markdown 中插入图片
autocmd FileType markdown nmap <buffer><silent> <leader>i :call mdip#MarkdownClipboardImage()<CR>
let g:mdip_imgdir = '.'
let g:mdip_imgname = 'Image'

" tmux 前缀是 c-z
noremap <c-z> <NOP>


set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'

" 给配对的 {} () 配色
Plugin 'luochen1990/rainbow'
" 基于git 标记新增，删除，和修改
Plugin 'airblade/vim-gitgutter'
" vim 中添加 GIT 命令
Plugin 'tpope/vim-fugitive'
" 文件浏览
Plugin 'scrooloose/nerdtree'
" 函数列表
Plugin 'majutsushi/tagbar'
" 文件快速搜索
Plugin 'kien/ctrlp.vim'
" 主题
Plugin 'flazz/vim-colorschemes'
" 状态栏
Plugin 'Lokaltog/vim-powerline'
" 成对的{},自动补全
Plugin 'jiangmiao/auto-pairs'
" 自动格式化代码
Plugin 'tell-k/vim-autopep8'
" 快速注释
Plugin 'scrooloose/nerdcommenter'
" 搜索工具
Plugin 'dyng/ctrlsf.vim'

" 代码补全
Plugin 'MarcWeber/vim-addon-mw-utils'
Plugin 'tomtom/tlib_vim'
Plugin 'SirVer/ultisnips'
" Tab快捷键具有更快捷的上下文提示功能
Bundle 'ervandew/supertab'
" markdown 插件
Plugin 'godlygeek/tabular'
Plugin 'plasticboy/vim-markdown'
Plugin 'mzlogin/vim-markdown-toc'
" markdown 预览
Bundle 'iamcco/mathjax-support-for-mkdp'
Plugin 'git@github.com:iamcco/markdown-preview.vim.git'
" install image in vim
Plugin 'ferrine/md-img-paste.vim'
" vim 标记
Bundle "kshenoy/vim-signature.git"
Plugin 'mileszs/ack.vim'
" 自动缩进
Plugin 'nathanaelkane/vim-indent-guides'

"
"" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required

" To ignore plugin indent changes, instead use:

" hi comment ctermfg=2

" autocmd FileType python set omnifunc=pythoncomplete#Complete
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line
