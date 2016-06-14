
.. toctree::
  :hidden:


Workflow of Tocc Development
============================

Picking Up Issues
-----------------

For each required change (Bug or Enhancement) there's an issue in
`Tocc's Issue List <https://github.com/aidin36/tocc/issues>`_.
To start work on something, you need to pick one of the issues.

Some issues labeled *easy*. If you are new to Tocc, we recommend to start with
one of them. After you get familiar with Tocc's design, you can pick other
issues.

To pick up an issue, leave a comment like *I'm going to work on this* on that
issue. Project's admin will add a label to that issue, so others know someone
working on it.

Cloning
-------
First, you need to clone the *master* branch of the main repository
(*aidin36*). To do so, go to the
`Tocc's Github Page <https://github.com/aidin36/tocc>`_ and click on *Fork*
button.

Now clone it on your local machine::

  git clone https://user@github.com/user/tocc.git

Branching
---------
You should create a branch for each issue you're working on. To do so,
follow these steps.

* Ensure your *master* branch is up to date::

     git checkout master
     git pull https://github.com/aidin36/tocc.git master

* Create a branch for the issue, and switch into it::

    git checkout -b issue92

* Do your changes, and commit them locally. (Don't forget to follow the
   :doc:`coding_style`.)

Sending Pull Request
--------------------
In order to merge your changes into main repository (*aidin36*), you need to
send a *Pull Request* that contains your changes. In order to that, follow
these steps.

* Push your branch to your Github account::

    git push origin issue92

* Go to Github site, and navigate to your fork of Tocc. Click on *Branch*
   menu. You should see your *issue92* branch. Click on *Create Pull Request*.

More Info
---------
Take a look at `Github help page <https://help.github.com/>`_ if you want full
info about how to work with Git and Github.


