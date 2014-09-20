# Edited by tugis (http://drupal.org/user/780690)

Welcome to Simplenews Content Selection.
This module allows you to select content from your website and send a newsletter with the selected content.

################################
# Simplenews Content Selection #
################################

USAGE
- Configure module permissions
- Go to admin/config/simplenews/scs
  - Choose the "View Mode" to be used for content in newsletters
    - Configure the "newsletter" view mode for each content type (if you choose this display)
      - admin/structure/types/manage/<content_type>/display/newsletter
  - Choose the format for your newsletter. HTML requires the mimemail module (http://drupal.org/project/mimemail)
  - Choose the publish state for the newsletters created with SCS
  - Choose the content types you want to use in newsletters
- Go to admin/content/scs and create your newsletter

###########
# Theming #
###########

Multiple theming functions are available

THEME_SCS_NEWSLETTER_OUTPUT
Theme the whole body of the newsletter including table of contents and all the selected nodes.

THEME_SCS_NODE_OUTPUT
Theme the output of one single selected node

THEME_SCS_NODE_TITLES
Theme the table of contents
