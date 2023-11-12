In the gitlab board you find issues. 
This document describes the way issues propagate over the board.


# Backlog Lane

The product owner (Quirin Meyer) priortizes the backlog.

You as a devloper can add issues at the bottom of the backlog and ask the product owner to priortize them.

# Open Lane

Pick an issue according the the following guide-lines from the "Open" lane:
1. Start from the top, since those are the issues with highest priority.
1. Pick issues that are assigned to you or an issue that is not assigned to anyone yet.
1. If there is no issue in "Open" lane, pick the highest ranked issue from the backlog.

After picking an issue, drag it into the "In Progress" lane.


# In Progress Lane

- Put issues that you are working on into the "In Progress" lane.
- Make sure that the issues are assigned to you.
- If the issue has not been assigned to anyone yet, but you decide to work in it, assign it to yourself.
- Work on the issue.

# Review Lane

You as a developer shall do the following things once you feel an issue is completed and you want it to be reviewed:
1. After completing the issue drag it into "In Review" lane.
1. Change the assignee to the person that should review your changes.
1. Note in the comments of the issue 
- that it is ready to review and 
- provide the commit number(s) in the comments.

You as a reviewer shall do the following things:
1. Review the issue by looking reviewing all commit numbers noted in the issue comments.
2. In case you accept the issue put the issue into the "Closed" lane.
Make a short note in the comments of the issue that you closed it. 
3. In case you do not accept the issue:
- Make comment in the commit about what you dislike.
- Note  in the issue comments that you dislike the changes.
- Put the issue back into the "In Progress" lane.
4. In any case assign the issue back to the original author, after you have done the review.

# Closed Lane

This is where you as review put issues that passed you review.


