# Storybook-markup

Show markup from your react stories in the storybook panel.

## usage

In .storybook/addons.js

```js
import "@storybook/addon-actions/register";

import "storybook-markup/src/register";
```

In your stories file

```js
<ShowMarkup>
  <Button onClick={action("clicked")}>Hello Button</Button>
</ShowMarkup>
```

## contributing

This addon is developed in ReasonML. Just update the .re files and start with `yarn run start`.
