-- print('---: ', ddakong.fdread, ddakong.fdwrite)

ddakong.set_current_handle_input_fn(function(fd_keyin, fd_child)
      local buf = ddakong.fdread(fd_keyin, 1)
      ddakong.fdwrite(fd_child, buf)
end)

