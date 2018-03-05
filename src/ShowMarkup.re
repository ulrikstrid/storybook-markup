let component = ReasonReact.statelessComponent("ShowMarkup");

let make = children => {
  ...component,
  didMount: _self => {
    let channel = Addons.getChannel(Addons.addons, ());
    Addons.emitChannel(
      channel,
      "ulrikstrid/storybook-markup/show_markup",
      ReactDOMServerRe.renderToStaticMarkup(children)
    );
    ReasonReact.NoUpdate;
  },
  render: _self => children
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps => make(jsProps##children));
