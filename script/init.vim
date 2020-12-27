filetype off                  " required
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
set selection=exclusive
set selectmode=mouse,key
set matchtime=5
set ignorecase      "忽略大小写"
set hlsearch        "高亮搜索项"
set whichwrap+=<,>,h,l
set autoread
set directory=~/vimswap
set tags=tags
syntax on
set hlsearch
set cindent
set cinoptions=:0,l1,t0,g0,+10,(0,+s    " Linux Kernel CodingStyle
set completeopt=longest,menuone
set ts=4
set softtabstop=4
set shiftwidth=4


let g:solarized_termcolors=256  "solarized主题设置在终端下的设置"
let g:molokai_original = 1
let g:rehash256 = 1
let g:UltiSnipsUsePythonVersion = 3

autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 0 && !exists("s:std_in") | NERDTree | endif

fun! <SID>StripTrailingWhitespaces()
    let l = line(".")
    let c = col(".")
    %s/\s\+$//e
    call cursor(l, c)
endfun

autocmd BufWritePre * :call <SID>StripTrailingWhitespaces()


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

" move
map <c-l> <c-w>l
map <c-k> <c-w>k
map <c-j> <c-w>j
map <c-h> <c-w>h
" heighlight
colorscheme 1989


"for nerdtree
let NERDTreeIgnore=['\.pyc','\~$','\.swp','\.out','tags']
let NERDTreeShowBookmarks=1

" file explore
map <C-n> :NERDTreeToggle<CR>
" taglist
nmap <C-f> :TagbarToggle<CR>
map g<C-]> :cs find 3 <C-R>=expand("<cword>")<CR><CR>
" snip config
" let g:UltiSnipsSnippetDirectories=["~/.vim/Snippets"]


" better key bindings for UltiSnipsExpandTrigger
let g:UltiSnipsExpandTrigger="<c-e>"
let g:UltiSnipsJumpForwardTrigger="<c-j>"
let g:UltiSnipsJumpBackwardTrigger="<c-k>"
set foldmethod=indent
set foldlevel=99
let g:ctrlp_max_height = 15

"C Call Tree
let CCTreeEnhancedSymbolProcessing = 1


" set list
highlight RedundantSpaces ctermbg=red guibg=red
set list listchars=tab:▷\ ,nbsp:]

function PRINT()
    call append(line("."), "printk(\"[%s] [%s],[%d]\\n\",TAG, __FUNCTION__,__LINE__);")
endfunction

" make YCM compatible with UltiSnips (using supertab)
let g:ycm_key_list_select_compltion = ['<alt-q>', '<Down>']
let g:ycm_key_list_previous_completion = ['<alt-a>', '<Up>']
let g:SuperTabDefaultCompletionType = '<alt-z>'
let g:ycm_key_invoke_completion = '<c-space>'
"自动开启语义补全

let g:ycm_add_preview_to_completeopt = 0
let g:ycm_show_diagnostics_ui = 0
let g:ycm_server_log_level = 'info'
let g:ycm_min_num_identifier_candidate_chars = 2
let g:ycm_collect_identifiers_from_comments_and_strings = 1
let g:ycm_complete_in_strings=1
let g:ycm_key_invoke_completion = '<c-z>'
set completeopt=menu,menuone

noremap <c-z> <NOP>

let g:ycm_semantic_triggers =  {
            \   'c' : [],
            \   'cs,java,javascript,typescript,d,python,perl6,scala,vb,elixir,go' : ['.'],
            \   'lua' : [],
            \ }

let g:ycm_seed_identifiers_with_syntax = 0

"highlight Search ctermbg=yellow ctermfg=black
"highlight IncSearch ctermbg=black ctermfg=yellow
highlight MatchParen cterm=underline ctermbg=NONE ctermfg=NONE
set incsearch


nnoremap <F4> : nohl <CR>
nnoremap <F2> : set clipboard=unnamed <CR>
nnoremap <F3> : set clipboard^=unnamed,unnamedplus <CR>
nmap <F5> : call PRINT() <cr>

nmap <silent> <F6> <Plug>MarkdownPreview
imap <silent> <F6> <Plug>MarkdownPreview
nmap <silent> <F7> <Plug>StopMarkdownPreview
imap <silent> <F7> <Plug>StopMarkdownPreview

let g:vmt_auto_update_on_save = 0
let g:vmt_dont_insert_fence = 1
let g:vmt_cycle_list_item_markers = 1


let mapleader=","

" insert image in vim
autocmd FileType markdown nmap <buffer><silent> <leader>i :call mdip#MarkdownClipboardImage()<CR>
let g:mdip_imgdir = '.'
let g:mdip_imgname = 'Image'

" Ack setting
nmap <leader>r : execute "Ack " .expand('<cword>') ." -i " ."./ --cc --cpp --asm --lua" <CR><CR>
nmap <leader>o :copen <CR>
nmap <leader>c :cclose <CR>
nnoremap <leader>n : cnext <CR>
nnoremap <leader>l : cprev <CR>

let g:indent_guides_enable_on_vim_startup=1
" 从第二层开始可视化显示缩进
let g:indent_guides_start_level=1
" 色块宽度
let g:indent_guides_guide_size=1
" 快捷键 i 开/关缩进可视化
nmap <Leader>t <Plug>IndentGuidesToggle

hi IndentGuidesOdd  ctermbg=black
hi IndentGuidesEven ctermbg=darkgrey


" for markdown
" let g:vim_markdown_folding_level = 6
" let g:vim_markdown_toc_autofit = 1
"au BufRead,BufNewFile *.md colorscheme OceanicNext

let g:pydiction_location = '~/.vim/bundle/Pydiction/complete-dict'
let g:pydiction_menu_height = 20

set cursorline
let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlP'
let g:ctrlp_custom_ignore = '\v[\/]\.(git|hg|svn|pyc)$'

" gitgutter
set updatetime=100
let g:gitgutter_sign_added = '++'
let g:gitgutter_sign_modified = 'xx'
let g:gitgutter_sign_removed = '--'
let g:gitgutter_max_signs=1500

highlight GitGutterAdd    guifg=#009900 ctermfg=2
highlight GitGutterChange guifg=#bbbb00 ctermfg=3
highlight GitGutterDelete guifg=#ff2222 ctermfg=1



set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'

Plugin 'tpope/vim-fugitive'
Plugin 'git://git.wincent.com/command-t.git'
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}

Plugin 'scrooloose/nerdtree'
Plugin 'majutsushi/tagbar'
Plugin 'Valloric/YouCompleteMe'
Plugin 'kien/ctrlp.vim'
Plugin 'tomasr/molokai'
Plugin 'tpope/vim-surround'
Plugin 'pangloss/vim-javascript'
" add to .vimrc
Plugin 'flazz/vim-colorschemes'

" Plugin 'scrooloose/syntastic'
Plugin 'nvie/vim-flake8'
Plugin 'jnurmine/Zenburn'
Plugin 'altercation/vim-colors-solarized'

Plugin 'Lokaltog/vim-powerline'
" Plugin 'Yggdroot/indentLine'
Plugin 'jiangmiao/auto-pairs'
Plugin 'tell-k/vim-autopep8'
Plugin 'scrooloose/nerdcommenter'

" Plugin 'davidhalter/jedi-vim'
Plugin 'BurntSushi/ripgrep.git'
" Plugin 'hari-rangarajan/CCTree'
Plugin 'MarcWeber/vim-addon-mw-utils'
Plugin 'tomtom/tlib_vim'
Plugin 'honza/vim-snippets'
Plugin 'SirVer/ultisnips'
Plugin 'garbas/vim-snipmate'
Bundle 'ervandew/supertab'

" for markdown

Plugin 'godlygeek/tabular'
Plugin 'plasticboy/vim-markdown'
Plugin 'mzlogin/vim-markdown-toc'
"Plug 'iamcco/markdown-preview.nvim'

" vim mark
Bundle "kshenoy/vim-signature.git"

" for markdown preview
Bundle 'iamcco/mathjax-support-for-mkdp'
Plugin 'git@github.com:iamcco/markdown-preview.vim.git'

" install image in vim
Plugin 'ferrine/md-img-paste.vim'
Plugin 'mileszs/ack.vim'

" for git
Plugin 'airblade/vim-gitgutter'
" utilsnip

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
