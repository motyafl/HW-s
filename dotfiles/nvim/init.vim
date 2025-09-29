source ~/.config/nvim/vim-plug/pluggins.vim
lua require("toggleterm").setup()
nnoremap <C-f> :Telescope
set termguicolors     " enable true colors support
let ayucolor="light"  " for light version of theme
let ayucolor="mirage" " for mirage version of theme
let ayucolor="dark"   " for dark version of theme
colorscheme ayu
