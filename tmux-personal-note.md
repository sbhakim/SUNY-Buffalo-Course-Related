<h2>Using TMUX utility </h2>



**Creating New session**


	$tmux new -s  <mysession> 


**Checking the list of sessions**

	$tmux ls 

**Detaching a session  (keyboard shortcut)**
	
	ctrl+b    D 
	
**How to re-attach to a session**

	$tmux attach -t <mysession>
	
**To create horizontal panes  (keyboard shortcut)** 

	ctrl+b   %

**To switch between panes  (keyboard shortcut)**

	ctrl+b   ←     and       ctrl+b   →

**Creating a pane in the bottom**

	ctrl+b  "
	
**To destroy a pane**
	
	$exit
	
**Resizing the panes**

	ctrl+b   :
	:resize-pane   -R   20     
	:resize-pane   -D  20
	
[resizing-details](https://michaelsoolee.com/resize-tmux-panes/) 

**Killing a particular session**

	$tmux kill-session -t <mysession>
	
**Killing all sessions at once**

	$tmux  kill-server      
	or
	$tmux kill-session -a